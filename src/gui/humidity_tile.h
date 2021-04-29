#ifndef HUMIDITY_TILE_H
#define HUMIDITY_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLineEdit>
#include <QProgressBar>

class humidity_tile : public dash_tile
{
    Q_OBJECT

    QLabel *water_label;
    QLineEdit *room_lights_opt_4;
    QLabel *room_label_4;
    QProgressBar *humidity_per;
public:
    humidity_tile();
};

#endif // HUMIDITY_TILE_H
