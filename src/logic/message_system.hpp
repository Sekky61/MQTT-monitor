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
#include <deque>

#include <sstream>
#include <algorithm>

#include "mqtt/async_client.h"

std::vector<std::string> cut_topic_path(std::string topic_name);

template<typename T>
class TreeNode
{
public:

	std::string Topic;
	std::string fullTopic;

	unsigned long limit;
	std::deque<T> Msgs;

    std::vector<TreeNode<T> *> Children;
	TreeNode<T> *Parent;

        TreeNode(): Parent(nullptr)  {}

    TreeNode(TreeNode<T> *parent_ptr, std::string topic_name, std::string full_topic) :
		Topic(topic_name),
		fullTopic(full_topic),
		limit(0),
		Msgs(),
		Children(),
		Parent(parent_ptr) {} // const T& value // todo move && ?

	T *get_latest_msg(){
		if (Msgs.empty()){
			return nullptr;
		}
		return &Msgs.back();
	}

	void set_limit_recursive(int new_limit){
		limit = new_limit;

		for(auto child : Children){
			child->set_limit_recursive(limit);
		}
	}

	void set_limit(int new_limit){
		limit = new_limit;

		while(limit != 0 && limit < Msgs.size()){
			std::cerr << "set_limit: Size is " << Msgs.size() << " limit is " << limit << " and I must pop\n";
			Msgs.pop_front();
		}
	}

	void set_topic(std::string topic){
		// todo checks
		Topic = topic;
	}

	void add_message(T message){
		if(limit != 0 && limit <= Msgs.size()){
			Msgs.pop_front();
			Msgs.push_back(message);
		} else {
			Msgs.push_back(message);
		}
	}

	TreeNode<T> *get_child(std::string name){
		auto x = std::find_if(Children.begin(), Children.end(), [&] (const TreeNode<T> *s) { return s->Topic == name; });
		if (x != Children.end()){
			// child exists
			return *x;
		}
		return nullptr;
	}

	TreeNode<T> *get_child_by_index(int index){
		if (index >= 0 && index < Children.size()){
			// child exists
			return Children[index];
		}
		return nullptr;
	}

	int get_number_of_children(){
		
		return Children.size();
	}

	int get_own_index(){
		if(!Parent){
			return -1;
		}
		auto it = find(Parent->Children.begin(), Parent->Children.end(), this);
		if (it != Parent->Children.end())
    	{
			// found
        	return it - Parent->Children.begin();
    	}
    	else {
        	return -1;
    	}
	}

	TreeNode<T> *get_create_child(std::string name){
		auto *child_node = get_child(name);
		if (child_node == nullptr){
			// child does not exists
			std::string new_full = (fullTopic == "" ? "" : fullTopic + "/" ) + name;
			TreeNode<T> *new_node = new TreeNode<T>(this, name, new_full);
			return Children.emplace_back(new_node);
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

void print_tree(TopicNode *root);

extern const std::string DEFAULT_SERVER_ADDRESS;

class MessageSystem
{
public:

	bool SubscribeAll;
    TopicNode *messages_root;
	std::vector<std::string> topics; // maybe list/map na odstranovani

	const int QOS {1};
	const std::string client_id;

	bool rewrite_session = true;

	mqtt::async_client client;

	MessageSystem(std::string client_name, std::string server_address):
		client_id{ client_name },
		client(server_address, client_id)
    {
		messages_root = new TopicNode();
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
	void set_limit_all(int new_limit);

	void add_topic(std::string topic_name);

	void remove_topic(std::string topic_name);

	void send_message(std::string topic, void *data, size_t data_len);

};

#endif // !MSG_SSTM
