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
    //cli.connect_to_server("mainName", "tcp://localhost:1888");
    //cli.sys->add_topic("cc/dd");
    TopicModel topmod(cli);

    MainWindow w;
    w.set_tree_model(&topmod);

    QObject::connect(&cli, &client::mqtt_data_changed, &topmod, &TopicModel::incoming_data_change);
    QObject::connect(&w, &MainWindow::connect_client_mainwindow, &cli, &client::user_clicked_connect);

    w.show();
    return a.exec();
}
