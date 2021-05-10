/*!
 *  \file      dash_tile.cpp
 *  \brief     Widget dashboardu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#include "dash_tile.h"

#include <QLayout>
#include <QPushButton>
#include <QLabel>

dash_tile::dash_tile(QWidget *parent, QString topic_src) :
    QFrame(parent),
    layout(new QGridLayout),
    topic(topic_src)
{
    this->setStyleSheet("dash_tile {\nborder: 2px solid rgb(37,39,48);\nborder-radius: 20px;\n}");
    setGeometry(QRect(0, 0, 320, 200));
    setMinimumSize(QSize(320, 200));

    setMaximumHeight(200);
    setMaximumWidth(320);

    setLayout(layout.get());
    setLayoutDirection(Qt::LeftToRight);
}
