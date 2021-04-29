#ifndef TEMPERATURE_TILE_H
#define TEMPERATURE_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLCDNumber>

class temperature_tile : public dash_tile
{
    Q_OBJECT

    QLCDNumber *lcdNumber_2;
    QLabel *temperature_label;
public:
    temperature_tile(QString);
};

#endif // TEMPERATURE_TILE_H
