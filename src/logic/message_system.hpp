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

/**
 * Alias pro strom zpráv
 */
using TopicNode = TreeNode<mqtt::const_message_ptr>;

/**
 * Výpis uzlu stromu. Debugovací účely
 */
std::ostream& operator<< (std::ostream &out, TopicNode const& node);

/**
 * Výpis stromu. Debugovací účely
 */
void print_tree(TopicNode *root);

/**
 * \class Klient MQTT
 * Ukládá zprávy do stromu podle témat, přijímá a odesílá zprávy
 */
class MessageSystem
{
public:

	/**
 	 * \brief Indikátor, jestli je klient připojený na server
 	 */
	bool connected;

	/**
 	 * \brief Kořen stromu uložených zpráv. Kořen je prázdný
 	 */
    std::unique_ptr<TopicNode> messages_root;

	/**
 	 * \brief Seznam odebíraných témat. Včetně wildcards
 	 */
	std::vector<std::string> topics; 

	/**
 	 * \brief Quality of service, parametr pro MQTT klient
 	 */
	const int QOS {1};

	/**
 	 * \brief Jméno klienta na serveru
 	 */
	const std::string client_id;

	/**
 	 * \brief MQTT klient knihovny Paho cpp
 	 */
	mqtt::async_client client;

	/**
 	  * \brief Konstruktor
	  * Nastaví callback pro každou přijatou zprávu. 
	  * Callback je při použití v \ref client přepsán callbackem s QT signály
 	 */
	MessageSystem(std::string client_name, std::string server_address):
		connected(false),
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
		});
	}

	/**
	 * \brief Destruktor.
	 * Pokud je klient připojen, korektně se od serveru odpojí.
	 */
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

	/**
	 * \brief Připojí klient k MQTT brokeru. Použije k tomu adresu a jméno předané v konstruktoru
	 */
	int connect_client();

	/**
	 * \brief Vyhodnotí, jestli je topic odebírán.
	 * \return true pokud téma je v seznamu témat
	 */
	bool is_subscribed_topic(std::string topic);

	/**
	 * \brief Vyhledá uzel odpovídající názvu tématu
	 * \return ukazatel na uzel, pokud existuje, jinak nullptr
	 */
	TopicNode *get_node_by_topic(std::string topic);

	/**
	 * \brief Vyhledá uzel odpovídající názvu tématu a přidá do něj zprávu. Název tématu je součástí objektu zprávy.
	 * \return úspěch operace
	 */
	bool add_message(mqtt::const_message_ptr);

	/**
	 * \brief Nastaví pro všechny uzly omezení na historii zpráv.
	 * \param new_limit nová maximální délka historie. Hodnota 0 značí, že historie nemá mít omezení
	 */
	void set_limit_all(int new_limit);

	/**
	 * \brief Vytvoří všechny potřebné uzly podle názvu tématu
	 * \param topic_name název tématu
	 */
	void add_topic(std::string topic_name);

	/**
	 * \brief Smaže náležité uzly z paměti a přestane odebírat téma specifikované parametrem
	 * \param topic_name název tématu
	 */
	void remove_topic(std::string topic_name);

	/**
	 * \brief Pošle na dané téma zprávu s obsahem proměnné data
	 * \param topic název tématu
	 * \param data ukazatel na začátek dat
	 * \param data_len délka dat odkazovaných v \ref data
	 */
	void send_message(std::string topic, const void *data, size_t data_len);

};

#endif // !MSG_SSTM
