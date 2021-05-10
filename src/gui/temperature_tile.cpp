/*!
 *  \file      temperature_tile.cpp
 *  \brief     Widget dashboardu - zobrazení teploty
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */

#include "temperature_tile.h"

temperature_tile::temperature_tile(QWidget *parent, QString topic_src) : dash_tile(parent, topic_src)
{
    lcdNumber_2 = new QLCDNumber(this);
    lcdNumber_2->setGeometry(QRect(60, 80, 191, 91));
    lcdNumber_2->setStyleSheet(QString::fromUtf8("QLCDNumber{\n"
    "border: 1px solid rgb(37,39,48);\n"
    "border-radius: 20px;\n"
    "}"));
    lcdNumber_2->setFrameShape(QFrame::StyledPanel);
    lcdNumber_2->setDigitCount(3);
    lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);

    temperature_label = new QLabel(this);
    temperature_label->setGeometry(QRect(10, 10, 141, 21));
    temperature_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    temperature_label->setText("Temperature");

    topic_label = new QLabel(this);
    topic_label->setGeometry(QRect(10, 35, 141, 21));
    topic_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    topic_label->setText(topic_src);
}

void temperature_tile::incoming_data(QString topic_src, QString payload)
{
    if(topic_src == topic){
        temperature = payload.toFloat();
        update_display();
    }
}

void temperature_tile::update_display()
{
    lcdNumber_2->display(QString("%1").arg(temperature, 0, 'f', 1));
}
