#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>

#include "../logic/message_system.hpp"

class client : public QObject
{
    Q_OBJECT
public:

    MessageSystem *sys;

    explicit client(QObject *parent = nullptr);

    int connect_to_server(QString, QString);

signals:

public slots:
    void user_clicked_connect(QString client_name, QString server_address);

};

#endif // CLIENT_H
