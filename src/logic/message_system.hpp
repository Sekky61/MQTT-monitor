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

std::vector<std::string> cut_topic_path(std::string topic_name){
	std::istringstream input;
    input.str(topic_name);

	std::vector<std::string> cut;
    for (std::string line; std::getline(input, line, '/'); ) {
    	cut.emplace_back(line);
	}
	return cut;
}

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
		std::cerr << "(node) Adding message " << Topic << ":" << message << std::endl;
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

		std::cerr << "Growing tree " << topic_name << std::endl;

		std::vector<std::string> cut = cut_topic_path(topic_name);

		TreeNode<T> *node = this;
		
		for(std::string name : cut){
			std::cerr << "\tgrowing > " <<  name << "\n";
			node = node->get_create_child(name);
		}
	}
};

using TopicNode = TreeNode<mqtt::const_message_ptr>;

std::ostream& operator<< (std::ostream &out, TopicNode const& node) {
    out << node.Topic << ": (";
    out << node.Msgs.size() << " msgs; " << node.Children.size() << " chldrn)";
    if(node.Msgs.size() != 0){
		out << "\n\tmsgs: ";
		for( auto msg : node.Msgs){
			out << msg->get_payload() << " | ";
		}
		out << "\n";
	}
    return out;
}

void print_tree(TopicNode& root){ // todo overload <<
	std::cerr << "printing: " << root.Topic << std::endl;
	std::cerr << root << '\n';
	for (auto &child : root.Children){
		std::cerr << "\tprinting child: " << child.Topic << std::endl;
		print_tree(child);
	}
}

const std::string SERVER_ADDRESS	{ "tcp://localhost:1888" };

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

    MessageSystem() : MessageSystem("clientid", "tcp://localhost:1888" ) { }

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

	int connect_client(); //todo do konstruktoru?
	int get_messages();
	bool is_subscribed_topic(std::string);
	TopicNode *get_node_by_topic(std::string);
	bool add_message(mqtt::const_message_ptr);

	void set_subscribe_all(bool subscribeAll){
		SubscribeAll = subscribeAll;
	}

	void add_topic(std::string topic_name){
		topics.emplace_back(topic_name);
		client.subscribe(topic_name, QOS)->wait();
		messages_root.grow_tree(topic_name);
	}

	void remove_topic(std::string topic_name){
		std::remove(topics.begin(),topics.end(), topic_name);
		client.unsubscribe(topic_name)->wait();
	}

};

bool MessageSystem::is_subscribed_topic(std::string topic){
	if(SubscribeAll){
		return true;
	}
	auto x = std::find(topics.begin(), topics.end(), topic);
	return x != topics.end();
}

// muze i vytvorit node nody
TopicNode *MessageSystem::get_node_by_topic(std::string topic){
	auto *node = &messages_root;

	auto cut = cut_topic_path(topic);

	for(std::string name : cut){
		node = node->get_create_child(name);
		if(node == nullptr){
			return nullptr;
		}
	}

	return node;
}

bool MessageSystem::add_message(mqtt::const_message_ptr message){
	if(!is_subscribed_topic(message->get_topic())){
		return false;
	}

	TopicNode *correct_node = get_node_by_topic(message->get_topic()); // pripadne vytvori node
	if(correct_node == nullptr){
		return false;
	}

	correct_node->add_message(message);
	return true;
}

int MessageSystem::connect_client(){

	auto connOpts = mqtt::connect_options_builder()
		.clean_session(false)
		.finalize();

	client.start_consuming();

	// Connect to the server

	std::cerr << "Connecting to the MQTT server..." << std::flush;
	auto tok = client.connect(connOpts);

	try {
		auto rsp = tok->get_connect_response();

		std::cerr << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "connect_client exc:\n  " << exc << std::endl;
		return 1;
	}
	return 0;
}

/*
// If we're here, the client was almost certainly disconnected.
		// But we check, just to make sure.

		if (cli.is_connected()) {
			cout << "\nShutting down and disconnecting from the MQTT server..." << flush;
			cli.unsubscribe(TOPIC)->wait();
			cli.stop_consuming();
			cli.disconnect()->wait();
			cout << "OK" << endl;
		}
		else {
			cout << "\nClient was disconnected" << endl;
		}
*/
