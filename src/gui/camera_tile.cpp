#include "camera_tile.h"

camera_tile::camera_tile() : dash_tile()
{
            cameras_label = new QLabel(this);
            cameras_label->setObjectName(QString::fromUtf8("cameras_label"));
            cameras_label->setGeometry(QRect(20, 10, 191, 21));
            //cameras_label->setFont(font2);
            cameras_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
            cameras_label->setText("Camera feed");
            room_lights_opt_2 = new QLineEdit(this);
            room_lights_opt_2->setObjectName(QString::fromUtf8("room_lights_opt_2"));
            room_lights_opt_2->setGeometry(QRect(140, 50, 151, 20));
            room_lights_opt_2->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
    "border: 2px solid rgb(37,39,48);\n"
    "border-left:none;\n"
    "border-right:none;\n"
    "border-top:none;\n"
    "border-radius: 20px;\n"
    "}"));
            room_lights_opt_2->setClearButtonEnabled(true);
            room_label_2 = new QLabel(this);
            room_label_2->setObjectName(QString::fromUtf8("room_label_2"));
            room_label_2->setGeometry(QRect(20, 50, 71, 16));
            room_label_2->setText("Room");
            //room_label_2->setFont(font2);
            snapshot_button = new QPushButton(this);
            snapshot_button->setObjectName(QString::fromUtf8("snapshot_button"));
            snapshot_button->setEnabled(true);
            snapshot_button->setGeometry(QRect(80, 130, 191, 41));
            snapshot_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
            snapshot_button->setText("Show last frame");
}
