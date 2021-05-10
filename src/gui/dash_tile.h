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
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <memory>

/*! 
 *  \brief     Třída dlaždice v dashboardu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */
class dash_tile : public QFrame
{
    Q_OBJECT

    std::unique_ptr<QGridLayout> layout;

public:

    /**
     * \brief topic, ke kterému se dlaždice váže
     */
    QString topic;

public:

    /**
     * \brief Konstruktor. Nastavuje styl dlaždice.
     * \param parent rodič v hierarchii QT objektů
     * \param topic_str téma
     */
    explicit dash_tile(QWidget *parent = nullptr, QString topic_src = "");


};

#endif // DASH_TILE_H
