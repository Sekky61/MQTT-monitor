/*!
 *  \file      thermostat_tile.cpp
 *  \brief     Widget dashboardu - ovládání teploty
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#include "thermostat_tile.h"

thermostat_tile::thermostat_tile(QWidget *parent, QString topic_src) : dash_tile(parent, topic_src)
{

    temp_button = new QPushButton(this);
    temp_button->setGeometry(QRect(130, 160, 151, 31));
    temp_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
    temp_button->setText("Set temperature");

    progressBar = new QProgressBar(this);
    progressBar->setGeometry(QRect(130, 130, 151, 23));
    progressBar->setMinimum(-50);
    progressBar->setMaximum(50);
    progressBar->setValue(24);
    progressBar->setTextVisible(false);

    lcdNumber = new QLCDNumber(this);
    lcdNumber->setGeometry(QRect(130, 50, 151, 71));
    lcdNumber->setStyleSheet(QString::fromUtf8("QLCDNumber{\n"
    "border: 1px solid rgb(37,39,48);\n"
    "border-radius: 20px;\n"
    "}"));
    lcdNumber->setFrameShape(QFrame::StyledPanel);
    lcdNumber->setDigitCount(3);
    lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    lcdNumber->setSmallDecimalPoint(true);

    heat_label = new QLabel(this);
    heat_label->setGeometry(QRect(10, 10, 141, 21));
    heat_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    heat_label->setText("Thermostat");

    topic_label = new QLabel(this);
    topic_label->setGeometry(QRect(10, 30, 141, 21));
    topic_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    topic_label->setText(topic_src);

    dial = new QDial(this);
    dial->setGeometry(QRect(10, 70, 91, 91));
    dial->setMinimum(-50);
    dial->setMaximum(50);
    dial->setInvertedAppearance(false);

    QObject::connect(dial, &QAbstractSlider::valueChanged, this, &thermostat_tile::on_dial_valueChanged);
    QObject::connect(temp_button, &QAbstractButton::clicked, this, &thermostat_tile::handle_click_set_temp);
}

void thermostat_tile::on_dial_valueChanged(int value)
{
    temperature = value;
    update_display();
}

void thermostat_tile::incoming_data(QString topic_src, QString payload)
{
    if(topic_src == topic){
        temperature = payload.toFloat();
        update_display();
    }
}

void thermostat_tile::update_display()
{
    dial->setValue(temperature);
    lcdNumber->display(QString("%1").arg(temperature, 0, 'f', 1));
    progressBar->setValue(temperature);
}

void thermostat_tile::handle_click_set_temp()
{
    emit send_data(topic, QString::number(temperature));
}
