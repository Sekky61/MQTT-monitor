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
    thermostat_tile(QString);

signals:

    void send_data(QString, QString);

public slots:

    void incoming_data(QString, QString);

private slots:
    void on_dial_valueChanged(int);
    void update_display();
    void handle_click_set_temp();
};

#endif // THERMOSTAT_TILE_H