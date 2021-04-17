#include "client.h"

client::client(QObject *parent) : QObject(parent)
{

}

int client::connect_to_server(QString client_name, QString server_address){
    sys = new MessageSystem(client_name.toStdString(), server_address.toStdString());
    return sys->connect_client();
}

void client::user_clicked_connect(QString client_name, QString server_address)
{
    std::cout << "Signal in its destination. name:" << client_name.toStdString() << "\n";
    connect_to_server(client_name, server_address);
}
