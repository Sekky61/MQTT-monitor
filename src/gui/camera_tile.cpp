/*!
 *  \file      camera_tile.cpp
 *  \brief     Widget dashboardu - zobrazení obrázků
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#include "camera_tile.h"

camera_tile::camera_tile(QWidget *parent, QString topic_src) :
    dash_tile(parent, topic_src)
{
    cameras_label = new QLabel(this);
    cameras_label->setGeometry(QRect(20, 10, 191, 21));
    cameras_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    cameras_label->setText("Camera feed");

    room_label_2 = new QLabel(this);
    room_label_2->setGeometry(QRect(20, 40, 250, 16));
    room_label_2->setText(topic_src);
    room_label_2->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));

    snapshot_button = new QPushButton(this);
    snapshot_button->setGeometry(QRect(40, 100, 240, 60));
    snapshot_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
        "background-color: rgb(77, 121, 140);"));
    snapshot_button->setText("Show last frame");

    QObject::connect(snapshot_button, &QPushButton::clicked, this, &camera_tile::show_camera_frame);
}

void camera_tile::show_camera_frame(bool)
{
    emit show_pic(topic);
}
