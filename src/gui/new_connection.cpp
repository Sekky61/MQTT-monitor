#include "new_connection.h"
#include "mainwindow.h"
#include "ui_new_connection.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QListWidget>
#include <QPlainTextEdit>

#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <iostream>
#include <QTimer>



void error_message(QString(text)){

    //QTimer::singleShot(2500, mbox, SLOT(hide()));
    QMessageBox msgBox(QMessageBox::Warning, "ERROR!!", text, QMessageBox::Ok);
    msgBox.exec();
}


void new_connection::save_profile(Profile profile_obj){
    //QString path = qApp->applicationDirPath();
    //QString filename = path + "//saved_connections.txt";
    QFile file("connection_profiles.csv");

    if(!file.exists()){
        error_message("Chyba při otevírání souboru");
    }

    if(file.open(QIODevice::Append | QIODevice::Text)){ //append zajistí nepřepisování souboru
        QTextStream stream(&file);
        stream << profile_obj.name;
        stream << ";";
        stream << profile_obj.username;
        stream << ";";
        stream << profile_obj.password;
        stream << ";";
        stream << profile_obj.protocol;
        stream << ";";
        stream << profile_obj.host;
        stream << ";";
        stream << profile_obj.port;
        stream << "\n";

        file.close();
    }
}

QList<Profile> load_profiles(){
    //otevřeme soubor s uloženými connections
    QFile file("connection_profiles.csv");

    if(!file.exists()){
        error_message("Chyba při otevírání souboru");
        return QList<Profile>();
    }

    QList<Profile> profiles;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            QString line = in.readLine();
            Profile prof = Profile(line);
            profiles.append(prof);
        }
        file.close();
    } else {
        error_message("Chyba při otevírání souboru");
        return QList<Profile>();
    }

    return profiles;
}

void remove_profile(int index){
    //otevřeme soubor s uloženými connections
    QFile file("connection_profiles.csv");

    if(!file.exists()){
        error_message("Chyba při otevírání souboru");
        return;
    }

    QStringList lines;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            lines.append(in.readLine());
        }
        file.close();
    } else {
        error_message("Chyba při otevírání souboru");
        return;
    }

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        for(int i = 0; i < lines.size();i++){
            if(i != index){
                std::cerr << "Writing back line " << i << " " << lines[i].toStdString() << std::endl;
                out << lines[i];
            }
        }
        file.close();
    } else {
        error_message("Chyba při otevírání souboru");
        return;
    }

}

new_connection::new_connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_connection)
{
    ui->setupUi(this);
    //ui->password_line->setPlaceholderText("Password"); //druhá možnost - místo labelů

    //ukládání connections
    model_con = new ProfilesListModel();
    model_con->profile_list = load_profiles();

    ui->listView->setModel(model_con);
    ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);


    //delete button enable
    ui->password_line->setClearButtonEnabled(true);
    ui->username_line->setClearButtonEnabled(true);
    ui->connectionName_line->setClearButtonEnabled(true);
    ui->protocol_line->setClearButtonEnabled(true);
    ui->host_line->setClearButtonEnabled(true);
    ui->port_line->setClearButtonEnabled(true);

}

new_connection::~new_connection()
{
    delete ui;
}


//zde bude kontrola připojení
void new_connection::on_connect_f_clicked()
{
    QString username = ui->username_line->text();
    QString password = ui->password_line->text();
    QString connection = ui->connectionName_line->text();
    QString protocol = ui->protocol_line->text();
    QString host = ui->host_line->text();
    QString port = ui->port_line->text();

    //ui->check_validate->isChecked()
    if(username=="test" && password=="12345"){
        error_message("username and password is correct");

    }else{
        error_message("username and password is incorrect");
    }


}

void new_connection::on_save_f_clicked()
{

    QString username = ui->username_line->text();
    QString password = ui->password_line->text();
    QString connection = ui->connectionName_line->text();
    QString protocol = ui->protocol_line->text();
    QString host = ui->host_line->text();
    QString port = ui->port_line->text();

    Profile new_profile;
    new_profile.username = username;
    new_profile.password = password;
    new_profile.name = connection;
    new_profile.protocol = protocol;
    new_profile.host = host;
    new_profile.port = port;

    save_profile(new_profile);
    model_con->profile_list = load_profiles();
    emit model_con->dataChanged(QModelIndex(), QModelIndex());
}

void new_connection::on_delete_button_clicked()
{
    if (ui->listView->model()->rowCount() == 0){
        error_message("Nelze smazat");
        return;
    }

    QModelIndex index = ui->listView->selectionModel()->selectedIndexes()[0];

    remove_profile(index.row());
    model_con->profile_list = load_profiles();
    emit model_con->dataChanged(QModelIndex(), QModelIndex());
}

int ProfilesListModel::rowCount(const QModelIndex &parent) const
{
    return profile_list.length();
}

QVariant ProfilesListModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        return QVariant(profile_list[index.row()].name);
    }
    return QVariant();
}

void new_connection::on_listView_doubleClicked(const QModelIndex &index)
{
    Profile prof = model_con->profile_list[index.row()];

    std::cerr << "Protocol: " << prof.protocol.toStdString() << std::endl;
    std::cerr << "Host: " << prof.host.toStdString() << std::endl;

    ui->username_line->setText(prof.username);
    ui->password_line->setText(prof.password);
    ui->connectionName_line->setText(prof.name);
    ui->protocol_line->setText(prof.protocol);
    ui->host_line->setText(prof.host);
    ui->port_line->setText(prof.port);
}
