#include "mainwindow.h"
#include "client.h"

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
    MainWindow w;

    QObject::connect(&w, &MainWindow::connect_client_mainwindow, &cli, &client::user_clicked_connect);

    w.show();
    return a.exec();
}
