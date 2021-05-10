/*!
 *  \file      humidity_tile.cpp
 *  \brief     Widget dashboardu - zobrazení vlhkosti
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#include "humidity_tile.h"

humidity_tile::humidity_tile(QWidget *parent, QString topic_src) : dash_tile(parent, topic_src)
{
    water_label = new QLabel(this);
    water_label->setGeometry(QRect(20, 10, 191, 21));
    water_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    water_label->setText("Humidity");

    topic_label = new QLabel(this);
    topic_label->setGeometry(QRect(20, 35, 191, 21));
    topic_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    topic_label->setText(topic_src);

    humidity_per = new QProgressBar(this);
    humidity_per->setGeometry(QRect(20, 110, 280, 41));
    humidity_per->setValue(0);
}

void humidity_tile::incoming_data(QString incoming_topic, QString payload)
{
    if(incoming_topic == topic){
        int val = payload.toInt();
        humidity_per->setValue(val);
    }
}
