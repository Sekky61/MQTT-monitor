/*! \file message_system.cpp
    \brief MQTT klient
    
	Trida MessageSystem pro prijem zprav z brokeru, ukladani zprav ve stromove strukture
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

#include <algorithm>

#include "message_system.hpp"

const std::string DEFAULT_SERVER_ADDRESS	{ "tcp://localhost:1888" };

std::ostream& operator<< (std::ostream &out, TopicNode *node) {
    out << node->Topic << ": (";
    out << node->Msgs.size() << " msgs; " << node->Children.size() << " chldrn)";
    if(node->Msgs.size() != 0){
		out << "\n\tmsgs: ";
		for( auto msg : node->Msgs){
			out << msg->get_payload() << " | ";
		}
		out << "\n";
	}
    return out;
}

void MessageSystem::set_subscribe_all(bool subscribeAll){
		SubscribeAll = subscribeAll;
}

void MessageSystem::set_limit_all(int new_limit){
	messages_root->set_limit_recursive(new_limit);
}

void MessageSystem::add_topic(std::string topic_name){
		topics.emplace_back(topic_name);
		client.subscribe(topic_name, QOS)->wait();

		if(messages_root != nullptr){
			messages_root->grow_tree(topic_name);
		} else {
			messages_root = std::make_unique<TopicNode>();
			messages_root->grow_tree(topic_name);
		}
        
	}

void MessageSystem::remove_topic(std::string topic_name){
        std::remove(topics.begin(), topics.end(), topic_name);
		client.unsubscribe(topic_name)->wait();

        auto node = get_node_by_topic(topic_name);

        if(node->is_start_of_wildcard){
            std::string actual_topic = topic_name + "/#";
            std::remove(topics.begin(), topics.end(), actual_topic);
        }

        auto parent = node->Parent;

        if(parent == nullptr){
            return;
        }

        auto &children = parent->Children;

        auto object_it = find_if(children.begin(), children.end(),
                        [&](std::unique_ptr<TopicNode> & obj){ return obj.get() == node;}
                       );
        if(object_it != children.end()){
            children.erase(std::remove(children.begin(), children.end(), *object_it));
        }
	}

bool MessageSystem::is_subscribed_topic(std::string topic){
	if(SubscribeAll){
		return true;
	}
	auto x = std::find(topics.begin(), topics.end(), topic);
	return x != topics.end();
}

// muze i vytvorit node nody
TopicNode *MessageSystem::get_node_by_topic(std::string topic){
	return messages_root->grow_tree(topic);
}

bool MessageSystem::add_message(mqtt::const_message_ptr message){

	TopicNode *correct_node = get_node_by_topic(message->get_topic()); // pripadne vytvori node - pripad wildcard
	if(correct_node == nullptr){
		return false;
	}

	correct_node->add_message(message);
	return true;
}

int MessageSystem::connect_client(){

	auto connOpts = mqtt::connect_options_builder()
		.finalize();

	client.start_consuming();

	// Connect to the server

	std::cerr << "Connecting to the MQTT server... name: " << client.get_client_id() << std::endl;
    try {
        auto tok = client.connect(connOpts);

		auto rsp = tok->get_connect_response();

		std::cerr << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "connect_client exc:\n\t" << exc << std::endl;
		return 1;
	}

	connected = true;
	return 0;
}

void MessageSystem::send_message(std::string topic, const void *data, size_t data_len){
	client.publish(topic, data, data_len);
}

// todo move

void print_tree(TopicNode *root){ // todo overload <<
    std::cerr << "printing: " << root->Topic << std::endl;
	std::cerr << root << '\n';
    for (auto &child : root->Children){
		std::cerr << "\tprinting child: " << child->Topic << std::endl;
        print_tree(child.get());
	}
}
