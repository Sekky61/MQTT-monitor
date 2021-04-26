#include "mainwindow.h"
#include "client.h"
#include "topicmodel.h"

#include <QApplication>
#include <QFile>
#include <QFileSystemModel>
#include <QtGui>
#include <QTreeView>
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    client cli;

    TopicModel topmod(cli);

    MainWindow w;
    w.set_tree_model(&topmod);

    QObject::connect(&cli, &client::mqtt_data_changed, &topmod, &TopicModel::incoming_data_change);
    QObject::connect(&w, &MainWindow::connect_client_mainwindow, &cli, &client::user_clicked_connect);
    QObject::connect(&cli, &client::connection_succesful, &w, &MainWindow::connection_succesful_slot);

    // add_topic_clicked
    QObject::connect(&w, &MainWindow::add_topic_clicked, &cli, &client::add_topic_slot);
    QObject::connect(&w, &MainWindow::delete_topic_clicked, &cli, &client::delete_topic_slot);
    QObject::connect(&w, &MainWindow::publish_clicked, &cli, &client::publish_slot);

    w.show();
    return a.exec();
}
