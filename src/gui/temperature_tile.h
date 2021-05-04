/*!
 *  \file      temperature_tile.h
 *  \brief     Widget dashboardu - zobrazení teploty
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */

#ifndef TEMPERATURE_TILE_H
#define TEMPERATURE_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLCDNumber>


/*! 
 *  \brief     Třída widgetu zobrazující teplotu
 *  \details   Dashboard dlaždice zobazující teplotu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */
class temperature_tile : public dash_tile
{
    Q_OBJECT

    QLCDNumber *lcdNumber_2;

    QLabel *temperature_label;
    QLabel *topic_label;

    float temperature;

  /*! 
   *  \brief  Překreslí lcd displej
   */
    void update_display();
public:
  /*!
     * \brief Konstruktor
     * \param parent rodič v hierarchii QT widgetů
     * \param topic_src téma, které bude s widgetem provázané
     */
    temperature_tile(QWidget *parent, QString topic_src);

public slots:
  /*! 
   *  \brief     Zpracování příchozích dat
   *  \details   Slot přijme téma a jeho hodnotu, tato hodnota je pak zobrazena na displeji
   *  \param     topic_src Aktuální téma ve kterém se nacházíme
   *  \param     payload Obsah tohoto tématu - je převedeno na float
   *  \post      po následném volání update_display() je hodnota topicu zobrazena na displeji
   */
    void incoming_data(QString topic_src, QString payload);
};

#endif // TEMPERATURE_TILE_H