/*!
 *  \file      light_tile.h
 *  \brief     Widget dashboardu - ovládání světla
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */

#ifndef LIGHT_TILE_H
#define LIGHT_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLineEdit>
#include <QRadioButton>


/*! 
 *  \brief     Třída widgetu Světla
 *  \details   Dashboard dlaždice ovládající světlo
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */
class light_tile : public dash_tile
{
    Q_OBJECT

    QLineEdit *device_lights_opt;

    QLabel *lights_label;
    QLabel *topic_label;

    QLineEdit *room_lights_opt;
    QLabel *room_label;
    QLabel *device_label;

    QPushButton *light_on_button;
    QPushButton *light_off_button;

    bool value;

    QString stylesheet_active = "color: rgb(255, 255, 255);\n"
    "background-color: rgb(66, 245, 99);";

    QString stylesheet_normal = "color: rgb(255, 255, 255);\n"
    "background-color: rgb(201, 201, 201);";

  /*! 
   *  \brief     Překreslí tlačítka dlaždice
   *  \details   V jednu chvíli je barevně označen jeden z buttonu on/off, dle aktuální hodnoty
   */
    void update_view();

signals:

  /*! 
   *  \brief     Signál zajišťuje změnu hodnoty aktuálního tématu
   *  \details   Uživatel si zvolí novou hodnotu, ta je poslána do sítě
   *  \param     topic Aktuální téma ve kterém se nacházíme
   *  \param     value Obsah tohoto tématu
   */
    void send_data(QString topic, QString value);

public:
  /*!
     * \brief Konstruktor
     * \param parent rodič v hierarchii QT widgetů
     * \param topic_src téma, které bude s widgetem provázané
     */
    light_tile(QWidget *parent, QString topic_src);

public slots:

  /*! 
   *  \brief     Zpracování příchozích dat
   *  \details   Slot přijme téma a jeho hodnotu, touto hodnotou je ovlivněn vzhled (stylesheet) buttonu
   *  \param     topic_src Aktuální téma ve kterém se nacházíme
   *  \param     payload Obsah tohoto tématu
   *  \post      po následném volání update_view() je hodnota topicu zobrazena na displeji
   */
    void incoming_data(QString topic_src, QString payload);

private slots:

  /*! 
   *  \brief     Slot zpracuje stisknutí tlačítka 'On'
   *  \details   Zašle zprávu "on"
   */
    void turn_on();

  /*! 
   *  \brief     Slot zpracuje stisknutí tlačítka 'Off'
   *  \details   Zašle zprávu "off"
   */
    void turn_off();
};

#endif // LIGHT_TILE_H