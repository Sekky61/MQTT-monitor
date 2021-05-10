/**
 *  \file      topicmodel.h
 *  \brief     Model - adapter mezi message_system a Qt views
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef TOPICMODEL_H
#define TOPICMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "client.h"
#include "../logic/message_system.hpp"

/**
 * \brief Model pro TreeView
 * \details Vrstva nad stromem \ref message_system
 */
class TopicModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    /**
     * \brief Konstruktor.
     * \param client_ref odkaz na klienta
     * \param parent rodič v hierarchii QT objektů
     */
    TopicModel(client &client_ref, QObject *parent = nullptr): QAbstractItemModel(parent), cli(client_ref) { };

    /**
     * \brief Vrací počet potomků v uzlu
     * \param parent odkaz rodičovský uzel
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * \brief Vrací počet sloupců v uzlu - 1 pokud obsahuje děti, jinak 0
     * \param parent odkaz rodičovský uzel
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * \brief Vrací data konkrétního indexu podle role
     * \param index odkaz na položku modelu
     * \param role typ požadovaných dat - textová, styl, font, ...
     */
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * \brief Vrací seznam názvů sloupců. V aplikaci se nevyužívá
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /**
     * \brief Vytvoří index na položku
     * \param row číslo řádku, který má index mít
     * \param column číslo sloupce, který má index mít
     * \param parent rodičovský index
     */
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    /**
     * \brief Vrací index rodiče
     * \param index index jehož rodiče chci získat
     */
    QModelIndex parent(const QModelIndex &index) const override;

public slots:

    /**
     * \brief Slot ragující na nadcházející změnu stromu témat
     * Parametry jsou nevyužity, existují kvůli kompatibilitě se signálem
     */
    void incoming_data_change(QString topic, QString message);

private:

    /**
     * Odkaz na klient, jehož strom modelujeme
     */
    client &cli;
};

#endif // TOPICMODEL_H
