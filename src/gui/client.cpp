#include "client.h"
#include "error_messages.h"
#include <QMessageBox>

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
                /*std::cerr
                    << "QT callback: " << topic
                    << " : " << msg << std::endl;*/
                emit mqtt_data_changed(QString::fromStdString(topic), QString::fromStdString(msg));
                std::cerr << "Emited mqtt_data_changed\n";
                this->sys->add_message(message);

                //print_tree(this->sys->messages_root.get());
            });

    int status = sys->connect_client();

    connected = (status == 0);

    return status;
}

void client::user_clicked_connect(QString client_name, QString server_address)
{
    std::cout << "User clicked connect. " << client_name.toStdString() << "\n";
    connect_to_server(client_name, server_address);

    if(connected){
        sys->add_topic("t1");
        sys->add_topic("t3");
        sys->add_topic("t2/sub1");
        sys->add_topic("t2/sub2");
        sys->add_topic("pic");
        emit connection_succesful();
        emit mqtt_data_changed("", "");
    } else {
        error_message("nepodarilo se pripojit");
    }
}

void client::user_clicked_disconnect()
{
    if(connected){
        sys->client.disconnect()->wait();
        connected = false;
        delete sys;
        sys = nullptr;
        std::cerr << "Disconnected.\n";
        emit mqtt_data_changed("", "");
    } else {
        std::cerr << "Neni pripojeno - nelze se odpojit\n";
    }
}

void client::add_topic_slot(QString topic_string)
{
    if(connected){
        sys->add_topic(topic_string.toStdString());
        emit mqtt_data_changed("", "");
    } else {
        std::cerr << "Nelze pridat topic " << topic_string.toStdString() << " - client neni pripojeny\n";
    }
}

void client::delete_topic_slot(QString topic_string)
{
    if(connected){
        sys->remove_topic(topic_string.toStdString());
        emit mqtt_data_changed("", "");
    } else {
        std::cerr << "Nelze odebrat topic " << topic_string.toStdString() << " - client neni pripojeny\n";
    }
}

void client::publish_slot(QString topic_string, QString content)
{
    if(connected){
        QByteArray data = QByteArray(content.toStdString().data());
        std::string topic = topic_string.toStdString();
        sys->send_message(topic, data.data(), data.length());

        emit mqtt_data_changed(topic_string, content);
    } else {
        std::cerr << "Nelze publishnout topic " << topic_string.toStdString() << " - client neni pripojeny\n";
    }
}
