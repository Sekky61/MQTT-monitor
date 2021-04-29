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
    light_tile(QString);

public slots:

    void incoming_data(QString, QString);

private slots:

    void turn_on();
    void turn_off();
};

#endif // LIGHT_TILE_H
