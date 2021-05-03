/*!
 *  \file      temperature_tile.h
 *  \brief     Widget dashboardu - zobrazení teploty
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

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
