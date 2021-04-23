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

    int connect_to_server(QString, QString);

signals:
    void connection_succesful();

    void mqtt_data_changed();

public slots:
    void user_clicked_connect(QString client_name, QString server_address);

    void add_topic_slot(QString topic_string);

    void publish_slot(QString topic_string, QString content); //todo void *

};

#endif // CLIENT_H
