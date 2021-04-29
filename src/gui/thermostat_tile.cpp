#include "thermostat_tile.h"

thermostat_tile::thermostat_tile(QString topic_src) : dash_tile(nullptr, topic_src)
{
    std::cerr << "constructing thermostat\n";

    temp_button = new QPushButton(this); //d
            temp_button->setObjectName(QString::fromUtf8("temp_button"));
            temp_button->setGeometry(QRect(130, 160, 151, 31));
            temp_button->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
    "background-color: rgb(77, 121, 140);"));
            temp_button->setText("Set temperature");
            progressBar = new QProgressBar(this); //d
            progressBar->setObjectName(QString::fromUtf8("progressBar"));
            progressBar->setGeometry(QRect(130, 130, 151, 23));
            progressBar->setMinimum(-50);
            progressBar->setMaximum(50);
            progressBar->setValue(24);
            progressBar->setTextVisible(false);
            lcdNumber = new QLCDNumber(this); //d
            lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
            lcdNumber->setGeometry(QRect(130, 50, 151, 71));
            lcdNumber->setStyleSheet(QString::fromUtf8("QLCDNumber{\n"
    "border: 1px solid rgb(37,39,48);\n"
    "border-radius: 20px;\n"
    "}"));
            lcdNumber->setFrameShape(QFrame::StyledPanel);
            lcdNumber->setDigitCount(3);
            lcdNumber->setSegmentStyle(QLCDNumber::Flat);
            lcdNumber->setSmallDecimalPoint(true);
            heat_label = new QLabel(this); //d
            heat_label->setObjectName(QString::fromUtf8("heat_label"));
            heat_label->setGeometry(QRect(10, 10, 141, 21));
            //heat_label->setFont(font2);
            heat_label->setStyleSheet(QString::fromUtf8("color:rgb(77, 121, 140);"));
            heat_label->setText("Thermostat");

            dial = new QDial(this); //d
            dial->setObjectName(QString::fromUtf8("dial"));
            dial->setGeometry(QRect(10, 40, 91, 91));
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
        temperature = payload.toInt();
        update_display();
    }
}

void thermostat_tile::update_display()
{
    dial->setValue(temperature);
    lcdNumber->display(temperature);
    progressBar->setValue(temperature);
}

void thermostat_tile::handle_click_set_temp()
{
    emit send_data(topic, QString::number(temperature));
}
