#include "client.h"

#include <QByteArray>

client::client(QObject *parent) : QObject(parent), connected(false), sys(nullptr)
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

    int status = sys->connect_client();

    connected = (status == 0);

    return status;
}

void client::user_clicked_connect(QString client_name, QString server_address)
{
    std::cout << "Signal in its destination. name:" << client_name.toStdString() << "\n";
    connect_to_server(client_name, server_address);

    if(connected){
        sys->add_topic("t1");
        sys->add_topic("t2/sub1");
        emit mqtt_data_changed();
    } else {
        // todo zobrazit zpravu ze se nepodarilo pripojit
    }
}

void client::add_topic_slot(QString topic_string)
{
    if(connected){
        sys->add_topic(topic_string.toStdString());
        emit mqtt_data_changed();
    } else {
        std::cerr << "Nelze pridat topic " << topic_string.toStdString() << " - client neni pripojeny\n";
    }
}

void client::publish_slot(QString topic_string, QString content)
{
    if(connected){
        QByteArray data = QByteArray(content.toStdString().data());
        sys->send_message(topic_string.toStdString(), data.data(), data.length());
        emit mqtt_data_changed();
    } else {
        std::cerr << "Nelze publishnout topic " << topic_string.toStdString() << " - client neni pripojeny\n";
    }
}
