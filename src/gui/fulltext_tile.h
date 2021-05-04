/*!
 *  \file      fulltext_tile.h
 *  \brief     Widget dashboardu - zobrazení textu
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef FULLTEXT_TILE_H
#define FULLTEXT_TILE_H

#include "dash_tile.h"
#include <QObject>
#include <QScrollArea>
#include <QPlainTextEdit>

class fulltext_tile : public dash_tile
{
    Q_OBJECT

    QLabel *pure_text;
    QLabel *topic_label;
    QScrollArea *scrollArea_5;
    QWidget *scrollAreaWidgetContents_5;
    QPlainTextEdit *value_text_2;

public:
    fulltext_tile(QWidget *, QString);

public slots:

    void incoming_data(QString topic, QString payload);
};

#endif // FULLTEXT_TILE_H
