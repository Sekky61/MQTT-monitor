#include "temperature_tile.h"

temperature_tile::temperature_tile(QString topic_src) : dash_tile(nullptr, topic_src)
{
    lcdNumber_2 = new QLCDNumber(this);
            lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
            lcdNumber_2->setGeometry(QRect(60, 60, 191, 91));
            lcdNumber_2->setStyleSheet(QString::fromUtf8("QLCDNumber{\n"
    "border: 1px solid rgb(37,39,48);\n"
    "border-radius: 20px;\n"
    "}"));
            lcdNumber_2->setFrameShape(QFrame::StyledPanel);
            lcdNumber_2->setDigitCount(3);
            lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
            temperature_label = new QLabel(this);
            temperature_label->setObjectName(QString::fromUtf8("temperature_label"));
            temperature_label->setGeometry(QRect(10, 10, 141, 21));
            //temperature_label->setFont(font2);
            temperature_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
            temperature_label->setText("Temperature");
}

void temperature_tile::incoming_data(QString topic_src, QString payload)
{
    if(topic_src == topic){
        temperature = payload.toInt();
        update_display();
    }
}

void temperature_tile::update_display()
{
    lcdNumber_2->display(temperature);
}
