#include "new_connection.h"
#include "mainwindow.h"
#include "ui_new_connection.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QListWidget>
#include <QPlainTextEdit>

void new_connection::writeToFile(QString(connection), QString(protocol),QString(host), QString(port),QString(username), QString(password)){
    QString path = qApp->applicationDirPath();
    QString filename = path + "//saved_connections.txt";
    QFile file(filename);

    if(file.open(QIODevice::Append | QIODevice::Text)){ //append zajistí nepřepisování souboru
        QTextStream stream(&file);
        stream << "\n";
        stream << connection;
        stream << ";";
        stream << protocol;
        stream << ";";
        stream << host;
        stream << ";";
        stream << port;
        stream << ";";
        stream << username;
        stream << ";";
        stream << password;
        stream << "\n";
    }
    file.close();
}


new_connection::new_connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_connection)
{
    ui->setupUi(this);
    //ui->password_line->setPlaceholderText("Password"); //druhá možnost - místo labelů

    //ukládání connections
    model_con = new QStringListModel(this);
    QStringList list_con; //array uložených connections

    model_con->setStringList(list_con);
 //   ui->listWidget->setModel(model_con);
    ui->listWidget->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);


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

    if(username=="test" && password=="12345"){
        QMessageBox::information(this, "Connect", "username and password is correct");
        if (ui->check_validate->isChecked()) {
            QMessageBox::information(this, "Check", "check validate certificate is on");
        }else{
            QMessageBox::information(this, "Check", "check validate certificate is off");
        }
    }else{
        QMessageBox::warning(this, "Connect", "username and password is incorrect");
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



    writeToFile(connection, protocol, host, port, username, password);

    //index kam uložit nové spojení
    int row = model_con->rowCount();
    model_con->insertRows(row,1);
    QModelIndex index = model_con->index(row);
    ui->listWidget->setCurrentIndex(index);

    //uložení protokolu do Qlist widget, příště už se načte ze souboru
    ui->listWidget->addItem(protocol);
}

void new_connection::on_delete_button_clicked()
{
    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete it;
}

void new_connection::on_loadButton_clicked()
{

    //otevřeme soubor s uloženými connections
    QString path = qApp->applicationDirPath();
    QString filename = path + "//saved_connections.txt";
    QFile file(filename);
    QStringList fields;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        while (!in.atEnd()){
            QString line = in.readLine();
            fields.append(line);
        }
        file.close();
    }

    QTextStream(stdout) << fields[0];
    QStringList attributes;
    for (int i = 0; i < fields.size(); ++i){
        //QTextStream(stdout) << fields.at(i).toLocal8Bit().constData() << Qt::endl;
        QString one_con = fields.at(i).toLocal8Bit().constData();
        attributes = one_con.split(";");
        for (int i = 0; i < attributes.size(); ++i){
            QTextStream(stdout) << attributes.at(i).toLocal8Bit().constData() << Qt::endl;
        }
        ui->listWidget->addItem(attributes.at(0));
    }
}
