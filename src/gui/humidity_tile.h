/*!
 *  \file      humidity_tile.h
 *  \brief     Widget dashboardu - zobrazení vlhkosti
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

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
    QLabel *topic_label;

    QLineEdit *room_lights_opt_4;
    QLabel *room_label_4;
    QProgressBar *humidity_per;
public:
    humidity_tile(QWidget *, QString);

public slots:
    void incoming_data(QString incoming_topic, QString payload);
};

#endif // HUMIDITY_TILE_H
