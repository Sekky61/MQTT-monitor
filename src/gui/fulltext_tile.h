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
    QScrollArea *scrollArea_5;
    QWidget *scrollAreaWidgetContents_5;
    QPlainTextEdit *value_text_2;

public:
    fulltext_tile(QWidget *, QString);

public slots:

    void incoming_data(QString topic, QString payload);
};

#endif // FULLTEXT_TILE_H
