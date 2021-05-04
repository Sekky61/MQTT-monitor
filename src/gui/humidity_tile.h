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

/*! 
 *  \brief     Třída widgetu Vlhkost
 *  \details   Dashboard dlaždice zobrazující vlhkost
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */
class humidity_tile : public dash_tile
{
    Q_OBJECT

    QLabel *water_label;
    QLabel *topic_label;

    QLineEdit *room_lights_opt_4;
    QLabel *room_label_4;
    QProgressBar *humidity_per;
public:
    /*!
     * \brief Konstruktor
     * \param parent rodič v hierarchii QT widgetů
     * \param topic_src téma, které bude s widgetem provázané
     */
    humidity_tile(QWidget *parent, QString topic_src);

public slots:
  /*! 
   *  \brief     Zpracování příchozích dat
   *  \details   Slot přijme téma a jeho hodnotu, tato hodnota je pak zobrazena na displeji
   *  \param     topic_src Aktuální téma ve kterém se nacházíme
   *  \param     payload Obsah tohoto tématu - je převedeno na int
   *  \post      hodnota topicu je zobrazena na displeji
   */
    void incoming_data(QString incoming_topic, QString payload);
};

#endif // HUMIDITY_TILE_H