#ifndef CAMERA_TILE_H
#define CAMERA_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLineEdit>

class camera_tile : public dash_tile
{
    Q_OBJECT

    QLabel *cameras_label;
    QLineEdit *room_lights_opt_2;
    QLabel *room_label_2;
    QPushButton *snapshot_button;

signals:
    void show_pic(QString);

public:

    camera_tile(QString);


private slots:

    void show_camera_frame(bool);
};

#endif // CAMERA_TILE_H