#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutapplication.h"
#include "new_connection.h"
#include "topicmodel.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}



MainWindow::~MainWindow()
{
    delete ui;
    //this->setCentralWidget(ui->textEdit);
}

void MainWindow::set_tree_model(TopicModel *mod)
{
    ui->treeView->setModel(mod);
}

void MainWindow::connect_to_client_from_dialog(QString client_name, QString server_address)
{
    std::cout << "Slot connect_to_client_from_dialog activated\n";
    emit connect_client_mainwindow(client_name, server_address);
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionAbout_Aplication_triggered()
{
    AboutApplication aboutapplication;
    aboutapplication.setModal(true);
    aboutapplication.exec();
}

void MainWindow::on_actionDefault_size_triggered()
{
    //ještě nevím co tady
    ui->textEdit->selectAll();
}

void MainWindow::on_buttonConnect_clicked()
{
    new_connection connection(this);

    QObject::connect(&connection, &new_connection::connect_to_server, this, &MainWindow::connect_to_client_from_dialog);
    connection.setModal(true);
    connection.exec();
}

void MainWindow::on_searchButton_clicked()
{
    //filtrování stromové struktury
    proxy_tree = new QSortFilterProxyModel(this);
    proxy_tree->setSourceModel(&model);
    proxy_tree->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxy_tree->setFilterKeyColumn(-1); //If the value is -1, the keys will be read from all columns
    proxy_tree->setFilterFixedString("broker");
}

void MainWindow::on_add_topic_clicked()
{
    //tree path - zde chceme přidat topic
    QString topic_path = ui->topic_search->text();
}

void MainWindow::on_copy_topic_2_clicked()
{
    ui->topic_search->setText("naše pozice ve stromové struktuře");
}

void MainWindow::on_delete_topic_2_clicked()
{
    //vymaže subtopics na této pozici
    QString topic_path = ui->topic_search->text();
}

void MainWindow::on_publish_button_clicked()
{
    QString message_path = ui->path_message->text(); //pošle zprávu na zadanou adresu
    QString text = ui->textEdit->toPlainText(); //zpráva
}
