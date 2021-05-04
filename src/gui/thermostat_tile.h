/*!
 *  \file      thermostat_tile.h
 *  \brief     Widget dashboardu - ovládání teploty
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef THERMOSTAT_TILE_H
#define THERMOSTAT_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QProgressBar>
#include <QLCDNumber>
#include <QDial>

/*! 
 *  \brief     Třída widgetu Termostat
 *  \details   Třída všech objektů nacházejících se v tomto widgetu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */
class thermostat_tile : public dash_tile
{
    Q_OBJECT

    QLabel *heat_label;
    QLabel *topic_label;
    QPushButton *temp_button;
    QProgressBar *progressBar;
    QLCDNumber *lcdNumber;
    QDial *dial;

    float temperature;

public:

    /*!
     * \brief Konstruktor
     * \param parent rodič v hierarchii QT widgetů
     * \param topic_src téma, které bude s widgetem provázané
     */
    thermostat_tile(QWidget *parent, QString topic_src);

signals:

  /*! 
   *  \brief     Signál zajišťuje změnu hodnoty aktuálního tématu
   *  \details   Uživatel si zvolí novou hodnotu pro termostat, tá je následně přepsána v aktuálním tématu
   *  \param     topic Aktuální téma ve kterém se nacházíme
   *  \param     value Obsah tohoto tématu
   */
    void send_data(QString topic, QString value);

public slots:

  /*! 
   *  \brief     Zpracování příchozích dat
   *  \details   Slot přijme téma a jeho hodnotu, tato hodnota je pak zobrazena na displeji
   *  \param     topic_src Aktuální téma ve kterém se nacházíme
   *  \param     payload Obsah tohoto tématu - je převedeno na float
   *  \post      po následném volání update_display() je hodnota topicu zobrazena na displeji
   */
    void incoming_data(QString topic_src, QString payload);

private slots:
  /*! 
   *  \brief     Slot přijme signál o změně hodnoty 
   *  \param value  nová hodnota
   */
    void on_dial_valueChanged(int value);


  /*! 
   *  \brief     Překreslí lcd displej
   *  \details   Hodnota je změněna na základě hodnoty widgetu dial
   */
    void update_display();

  /*! 
   *  \brief     Slot přijme signál o změně hodnoty termostatu
   *  \details   Uživatel si zvolí novou hodnotu pro termostat, tá je následně přepsána 
                 v aktuálním tématu - zajišťuje signál send_data
   */
    void handle_click_set_temp();
};

#endif // THERMOSTAT_TILE_H