#ifndef DASH_TILE_H
#define DASH_TILE_H

#include <QFrame>
#include <iostream>
#include <QLayout>
#include <QPushButton>
#include <QLabel>

class dash_tile : public QFrame
{
    Q_OBJECT

    std::unique_ptr<QGridLayout> layout;

public:
    explicit dash_tile(QWidget *parent = nullptr);


};

#endif // DASH_TILE_H
