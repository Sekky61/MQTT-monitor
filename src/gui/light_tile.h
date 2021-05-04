/*!
 *  \file      light_tile.h
 *  \brief     Widget dashboardu - ovládání světla
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef LIGHT_TILE_H
#define LIGHT_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLineEdit>
#include <QRadioButton>

class light_tile : public dash_tile
{
    Q_OBJECT

    QLineEdit *device_lights_opt;

    QLabel *lights_label;
    QLabel *topic_label;

    QLineEdit *room_lights_opt;
    QLabel *room_label;
    QLabel *device_label;

    QPushButton *light_on_button;
    QPushButton *light_off_button;

    bool value;

    QString stylesheet_active = "color: rgb(255, 255, 255);\n"
    "background-color: rgb(66, 245, 99);";

    QString stylesheet_normal = "color: rgb(255, 255, 255);\n"
    "background-color: rgb(201, 201, 201);";

    void update_view();

signals:

    void send_data(QString, QString);

public:
    light_tile(QWidget *, QString);

public slots:

    void incoming_data(QString, QString);

private slots:

    void turn_on();
    void turn_off();
};

#endif // LIGHT_TILE_H
