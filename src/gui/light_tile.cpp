#include "light_tile.h"

light_tile::light_tile() : dash_tile()
{
            device_lights_opt = new QLineEdit(this);
            device_lights_opt->setObjectName(QString::fromUtf8("device_lights_opt"));
            device_lights_opt->setGeometry(QRect(170, 70, 151, 20));
            device_lights_opt->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
    "border: 2px solid rgb(37,39,48);\n"
    "border-left:none;\n"
    "border-right:none;\n"
    "border-top:none;\n"
    "border-radius: 20px;\n"
    "}"));
            device_lights_opt->setClearButtonEnabled(true);
            lights_label = new QLabel(this);
            lights_label->setObjectName(QString::fromUtf8("lights_label"));
            lights_label->setGeometry(QRect(10, 10, 141, 21));
            //lights_label->setFont(font2);
            lights_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
            lights_label->setText("Light");
            room_lights_opt = new QLineEdit(this);
            room_lights_opt->setObjectName(QString::fromUtf8("room_lights_opt"));
            room_lights_opt->setGeometry(QRect(170, 40, 151, 20));
            room_lights_opt->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
    "border: 2px solid rgb(37,39,48);\n"
    "border-left:none;\n"
    "border-right:none;\n"
    "border-top:none;\n"
    "border-radius: 20px;\n"
    "}"));
            room_lights_opt->setClearButtonEnabled(true);

            room_label = new QLabel(this);
            room_label->setObjectName(QString::fromUtf8("room_label"));
            room_label->setGeometry(QRect(10, 40, 71, 16));
            //room_label->setFont(font2);
            room_label->setText("Room");
            device_label = new QLabel(this);
            device_label->setObjectName(QString::fromUtf8("device_label"));
            device_label->setGeometry(QRect(10, 70, 71, 16));
            //device_label->setFont(font2);
            device_label->setText("Device");

            light_set_button = new QPushButton(this);
            light_set_button->setObjectName(QString::fromUtf8("light_set_button"));
            light_set_button->setGeometry(QRect(170, 130, 151, 31));
            light_set_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
            light_set_button->setText("Set light");
            lights_on = new QRadioButton(this);
            lights_on->setObjectName(QString::fromUtf8("lights_on"));
            lights_on->setGeometry(QRect(230, 100, 47, 17));
            lights_on->setText("On");
            lights_off = new QRadioButton(this);
            lights_off->setObjectName(QString::fromUtf8("lights_off"));
            lights_off->setGeometry(QRect(280, 100, 41, 17));
            lights_off->setText("Off");
}
