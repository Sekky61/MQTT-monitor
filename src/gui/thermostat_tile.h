#ifndef THERMOSTAT_TILE_H
#define THERMOSTAT_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QProgressBar>
#include <QLCDNumber>
#include <QDial>

class thermostat_tile : public dash_tile
{
    Q_OBJECT

    QLabel *heat_label;
    QPushButton *temp_button;
    QProgressBar *progressBar;
    QLCDNumber *lcdNumber;
    QDial *dial;

    int temperature;

public:
    thermostat_tile();

private slots:
    void update_display();
    void send_data();
};

#endif // THERMOSTAT_TILE_H
