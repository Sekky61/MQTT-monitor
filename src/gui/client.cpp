#include "client.h"

client::client(QObject *parent) : QObject(parent)
{
    //sys = new MessageSystem();
}

int client::connect_to_server(QString client_name, QString server_address){
    sys = new MessageSystem(client_name.toStdString(), server_address.toStdString());

    sys->client.set_message_callback([this](const mqtt::const_message_ptr message){
                auto topic = message->get_topic();
                auto msg = message->get_payload();
                std::cerr
                    << "QT callback: " << topic
                    << " : " << msg << std::endl;
                emit mqtt_data_changed();
                std::cerr << "Emited mqtt_data_changed\n";
                this->sys->add_message(message);
                print_tree(this->sys->messages_root);
            });

    return sys->connect_client();
}

void client::user_clicked_connect(QString client_name, QString server_address)
{
    std::cout << "Signal in its destination. name:" << client_name.toStdString() << "\n";
    connect_to_server(client_name, server_address);

    sys->add_topic("t1");
    sys->add_topic("t2/sub1");
}
