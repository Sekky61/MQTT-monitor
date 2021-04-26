/*! \file message_system.hpp
    \brief Rozhrani MQTT klienta
    
	Trida MessageSystem pro prijem zprav z brokeru, ukladani zprav ve stromove strukture
*/

#ifndef MSG_SSTM
#define MSG_SSTM

#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <thread>
#include <chrono>
#include <vector>
#include <deque>

#include <algorithm>

#include "mqtt/async_client.h"
#include "tree_node.hpp"

using TopicNode = TreeNode<mqtt::const_message_ptr>;

std::ostream& operator<< (std::ostream &out, TopicNode const& node);

void print_tree(TopicNode *root);

extern const std::string DEFAULT_SERVER_ADDRESS;

class MessageSystem
{
public:

	bool connected;
	bool SubscribeAll;
    std::unique_ptr<TopicNode> messages_root;
	std::vector<std::string> topics; // maybe list/map na odstranovani

	const int QOS {1};
	const std::string client_id;

	bool rewrite_session = true;

	mqtt::async_client client;

	MessageSystem(std::string client_name, std::string server_address):
		connected(false),
        SubscribeAll(false),
		client_id{ client_name },
		client(server_address, client_id)
    {
		messages_root = std::make_unique<TopicNode>();
		client.set_message_callback([this](const mqtt::const_message_ptr message){
			auto topic = message->get_topic();
			auto msg = message->get_payload();
			std::cerr 
				<< "Callback: " << topic
				<< " : " << msg << std::endl;
			this->add_message(message);
			print_tree(this->messages_root.get());
		});
	}

	~MessageSystem() {
		if (client.is_connected()) {
			std::cerr << "\nShutting down and disconnecting from the MQTT server..." << std::flush;
			for(auto &topic: topics){
				client.unsubscribe(topic)->wait();
			}
			client.stop_consuming();
			client.disconnect()->wait();
			std::cerr << "OK" << std::endl;
		}
		else {
			std::cerr << "\nClient was disconnected" << std::endl;
		}
	}

	int connect_client();
	int get_messages();
	bool is_subscribed_topic(std::string);
	TopicNode *get_node_by_topic(std::string);
	bool add_message(mqtt::const_message_ptr);

	void set_subscribe_all(bool subscribeAll);
	void set_limit_all(int new_limit);

	void add_topic(std::string topic_name);

	void remove_topic(std::string topic_name);

	void send_message(std::string topic, const void *data, size_t data_len);

};

#endif // !MSG_SSTM
