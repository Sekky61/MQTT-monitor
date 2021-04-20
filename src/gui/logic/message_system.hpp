/*! \file message_system.hpp
    \brief Rozhrani MQTT klienta
    
    Trida TreeNode<T> implementujici strom.
	Trida MessageSystem pro prijem zprav z brokeru, ukladani zprav ve stromove strukture
*/

#ifndef MSG_SSTM
#define MSG_SSTM

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

#include <sstream>
#include <algorithm>

#include "mqtt/async_client.h"

std::vector<std::string> cut_topic_path(std::string topic_name);

template<typename T>
class TreeNode
{
public:

	std::string Topic;
	std::vector<T> Msgs;
    std::vector<TreeNode<T> > Children;

	TreeNode() {}

    TreeNode(std::string topic_name) : Topic(topic_name) {} // const T& value // todo move && ?

	T get_latest_msg(){
		return Msgs.back();
	}

	void set_topic(std::string topic){
		// todo checks
		Topic = topic;
	}

	void add_message(T message){
		Msgs.emplace_back(message);
	}

	TreeNode<T> *get_child(std::string name){
		auto x = std::find_if(Children.begin(), Children.end(), [&] (const TreeNode<T>& s) { return s.Topic == name; });
		if (x != Children.end()){
			// child exists
			return &(*x);
		}
		return nullptr;
	}

	TreeNode<T> *get_create_child(std::string name){
		auto *child_node = get_child(name);
		if (child_node == nullptr){
			// child does not exists
			return &Children.emplace_back(name);
		}
		return child_node;
	}

	void grow_tree(std::string topic_name){

		std::vector<std::string> cut = cut_topic_path(topic_name);

		TreeNode<T> *node = this;
		
		for(std::string name : cut){
			node = node->get_create_child(name);
		}
	}
};

using TopicNode = TreeNode<mqtt::const_message_ptr>;

std::ostream& operator<< (std::ostream &out, TopicNode const& node);

void print_tree(TopicNode& root);

extern const std::string DEFAULT_SERVER_ADDRESS;

class MessageSystem
{
public:

	bool SubscribeAll;
	TopicNode messages_root;
	std::vector<std::string> topics; // maybe list/map na odstranovani

	const int QOS {1};
	const std::string client_id;

	bool rewrite_session = true;

	mqtt::async_client client;

    MessageSystem() : MessageSystem("clientid", DEFAULT_SERVER_ADDRESS ) { }

	MessageSystem(std::string client_name, std::string server_address) : client_id{ client_name }, client(server_address, client_id)
    {
		client.set_message_callback([this](const mqtt::const_message_ptr message){
			auto topic = message->get_topic();
			auto msg = message->get_payload();
			std::cerr 
				<< "Callback: " << topic
				<< " : " << msg << std::endl;
			this->add_message(message);
			print_tree(this->messages_root);
		});
	}

	int connect_client();
	int get_messages();
	bool is_subscribed_topic(std::string);
	TopicNode *get_node_by_topic(std::string);
	bool add_message(mqtt::const_message_ptr);

	void set_subscribe_all(bool subscribeAll);

	void add_topic(std::string topic_name);

	void remove_topic(std::string topic_name);

};

#endif // !MSG_SSTM
