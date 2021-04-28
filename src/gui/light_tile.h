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
    QPushButton *light_set_button;
    QRadioButton *lights_on;
    QRadioButton *lights_off;
public:
    light_tile();
};

#endif // LIGHT_TILE_H
