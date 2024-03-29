#include "dash_tile.h"

#include <iostream>
#include <QLayout>
#include <QPushButton>
#include <QLabel>

dash_tile::dash_tile(QWidget *parent) :
    QFrame(parent),
    layout(new QGridLayout)
{
    std::cerr << "Dash tile constructed\n";
    this->setStyleSheet("dash_tile {\nborder: 2px solid rgb(37,39,48);\nborder-radius: 20px;\n}");
    setGeometry(QRect(0, 0, 320, 200));
    setMinimumSize(QSize(320, 200));

    setMaximumHeight(200);
    setMaximumWidth(320);

    setLayout(layout.get());
    setLayoutDirection(Qt::LeftToRight);
}
