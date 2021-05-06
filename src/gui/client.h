/*!
 *  \file      client.h
 *  \brief     MQTT klient
 *  \author    Michal Majer - xmajer21
 *  \author    Petr Pouč - xpoucp01
 *  \date      Datum vytvoření: 03.05.2021
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "../logic/message_system.hpp"

class client : public QObject
{
    Q_OBJECT
public:

    bool connected;
    MessageSystem *sys;

    explicit client(QObject *parent = nullptr);

    int connect_to_server(QString client_name, QString server_address);

signals:
    void connection_succesful();

    void mqtt_data_changed(QString topic, QString message);

public slots:
    void user_clicked_connect(QString client_name, QString password, QString server_address);

    void user_clicked_disconnect();

    void add_topic_slot(QString topic_string);

    void delete_topic_slot(QString topic_string);

    void publish_slot(QString topic_string, QString content); //todo void *

};

#endif // CLIENT_H
