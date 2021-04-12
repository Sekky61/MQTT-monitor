#include "new_connection.h"
#include "ui_new_connection.h"
#include <QMessageBox>

new_connection::new_connection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::new_connection)
{
    ui->setupUi(this);
    //ui->password_line->setPlaceholderText("Password"); //druhá možnost - místo labelů

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
}
