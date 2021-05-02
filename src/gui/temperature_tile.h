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

    int temperature;

    void update_display();
public:
    temperature_tile(QWidget *, QString);

public slots:
    void incoming_data(QString, QString);
};

#endif // TEMPERATURE_TILE_H
