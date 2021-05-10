/*!
 *  \file      main.cpp
 *  \brief     Vstupní bod aplikace
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */

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

    MainWindow w;

    w.show();
    return a.exec();
}
