/*!
 *  \file      dash_tile.h
 *  \brief     Widget dashboardu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef DASH_TILE_H
#define DASH_TILE_H

#include <QFrame>
#include <iostream>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <memory>

class dash_tile : public QFrame
{
    Q_OBJECT

    std::unique_ptr<QGridLayout> layout;

public:
    QString topic;

public:
    explicit dash_tile(QWidget *parent = nullptr, QString topic_src = "");


};

#endif // DASH_TILE_H
