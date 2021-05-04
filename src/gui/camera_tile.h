/*!
 *  \file      camera_tile.h
 *  \brief     Widget dashboardu - zobrazení obrázků
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef CAMERA_TILE_H
#define CAMERA_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QLineEdit>

/*! 
 *  \brief     Třída widgetu Kamera
 *  \details   Dashboard dlaždice zobrazující obrazová data
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 04.05.2021
 */
class camera_tile : public dash_tile
{
    Q_OBJECT

    QLabel *cameras_label;
    QLineEdit *room_lights_opt_2;
    QLabel *room_label_2;
    QPushButton *snapshot_button;

signals:

/*! 
 *  \brief     Signál zobrazí obrázek
 *  \details   Je zobrazen obrázek tématu předaného v signálu
 *  \pre       Téma v sobě musí obsahovat obrázek
 */
    void show_pic(QString);

public:

  /*!
     * \brief Konstruktor
     * \param parent rodič v hierarchii QT widgetů
     * \param topic_src téma, které bude s widgetem provázané
     */
    camera_tile(QWidget *parent, QString topic_src);


private slots:
  /*! 
   *  \brief     Slot přijme signál o že si uživatel přeje zobrazit obrázek
   *  \post      Po následném volání signálu show_pic je zobrazen obrázek obsažen v aktuálním tématu
   */
    void show_camera_frame(bool);
};

#endif // CAMERA_TILE_H