#include "humidity_tile.h"

humidity_tile::humidity_tile() : dash_tile()
{
    water_label = new QLabel(this);
            water_label->setObjectName(QString::fromUtf8("water_label"));
            water_label->setGeometry(QRect(20, 10, 191, 21));
            //water_label->setFont(font2);
            water_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
            water_label->setText("Humidity");

            room_lights_opt_4 = new QLineEdit(this);
            room_lights_opt_4->setObjectName(QString::fromUtf8("room_lights_opt_4"));
            room_lights_opt_4->setGeometry(QRect(140, 50, 151, 20));
            room_lights_opt_4->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
    "border: 2px solid rgb(37,39,48);\n"
    "border-left:none;\n"
    "border-right:none;\n"
    "border-top:none;\n"
    "border-radius: 20px;\n"
    "}"));
            room_lights_opt_4->setClearButtonEnabled(true);
            room_label_4 = new QLabel(this);
            room_label_4->setObjectName(QString::fromUtf8("room_label_4"));
            room_label_4->setGeometry(QRect(20, 50, 71, 16));
            //room_label_4->setFont(font2);
            room_label_4->setText("Room");

            humidity_per = new QProgressBar(this);
            humidity_per->setObjectName(QString::fromUtf8("humidity_per"));
            humidity_per->setGeometry(QRect(80, 110, 211, 41));
            humidity_per->setValue(24);
}
