#ifndef TOPICMODEL_H
#define TOPICMODEL_H

#include <QAbstractItemModel>
#include <QObject>

#include "client.h"
#include "../logic/message_system.hpp"

class TopicModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TopicModel(client &client_ref, QObject *parent = nullptr): QAbstractItemModel(parent), cli(client_ref) {

    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

public slots:
    void incoming_data_change(QString, QString);

private:
    client &cli;
};

#endif // TOPICMODEL_H
