#include "light_tile.h"

light_tile::light_tile() : dash_tile()
{
            device_lights_opt = new QLineEdit(this);
            device_lights_opt->setObjectName(QString::fromUtf8("device_lights_opt"));
            device_lights_opt->setGeometry(QRect(170, 70, 130, 20));
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
            room_lights_opt->setGeometry(QRect(170, 40, 130, 20));
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

            light_on_button = new QPushButton(this);
            light_on_button->setObjectName(QString::fromUtf8("light_set_button"));
            light_on_button->setGeometry(QRect(75, 130, 80, 50));
            light_on_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
            light_on_button->setText("On");

            light_off_button = new QPushButton(this);
            light_off_button->setObjectName(QString::fromUtf8("light_set_button"));
            light_off_button->setGeometry(QRect(165, 130, 80, 50));
            light_off_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
            light_off_button->setText("Off");

            QObject::connect(light_on_button, &QPushButton::clicked, this, &light_tile::turn_on);
            QObject::connect(light_off_button, &QPushButton::clicked, this, &light_tile::turn_off);
}

void light_tile::turn_on()
{
    //emit
}

void light_tile::turn_off()
{
    //emit
}
