#include "light_tile.h"

light_tile::light_tile(QWidget *parent, QString topic_src) : dash_tile(parent, topic_src)
{
    lights_label = new QLabel(this);
    lights_label->setGeometry(QRect(10, 10, 141, 21));
    lights_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    lights_label->setText("Light");

    topic_label = new QLabel(this);
    topic_label->setGeometry(QRect(10, 35, 141, 21));
    topic_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
    topic_label->setText(topic_src);

    light_on_button = new QPushButton(this);
    light_on_button->setGeometry(QRect(45, 100, 110, 50));
    light_on_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
    light_on_button->setText("On");

    light_off_button = new QPushButton(this);
    light_off_button->setGeometry(QRect(165, 100, 110, 50));
    light_off_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
    light_off_button->setText("Off");

    QObject::connect(light_on_button, &QPushButton::clicked, this, &light_tile::turn_on);
    QObject::connect(light_off_button, &QPushButton::clicked, this, &light_tile::turn_off);
}

void light_tile::incoming_data(QString topic_in, QString payload)
{
    if(topic_in == topic){
        value = payload.toLower() == "on";
        update_view();
    }
}

void light_tile::update_view()
{
    light_on_button->setStyleSheet(value ? stylesheet_active : stylesheet_normal);
    light_off_button->setStyleSheet(value ? stylesheet_normal : stylesheet_active);
}

void light_tile::turn_on()
{
    emit send_data(topic, "On");
}

void light_tile::turn_off()
{
    emit send_data(topic, "Off");
}
