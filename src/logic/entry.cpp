// debug entry point

#include <fstream>
#include <iterator>
#include <vector>

#include "message_system.hpp"

int main(int argc, char* argv[])
{
	MessageSystem sys("name7", DEFAULT_SERVER_ADDRESS);

	//std::cerr << "sys constructed. client name: " << sys.client.get_client_id() << "\n";

	int ret = sys.connect_client();
	if(ret != 0){
		std::cerr << "Client se nemohl pripojit.\n";
		return 1;
	}

	std::cerr << "About to sub" << std::endl;
	sys.add_topic("t1");
	sys.add_topic("t2/sub1");
	std::cerr << "subbed" << std::endl;

	std::cerr << sys.get_node_by_topic("t2/sub1")->Topic << std::endl;
	std::cerr << sys.get_node_by_topic("t2/sub1")->fullTopic << std::endl;

	std::ifstream input( "pic.png", std::ios::binary );

    // copies all data into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	std::cerr << "Sent pic.jpg - " << buffer.size() << " B\n";
	sys.send_message("pic", buffer.data(), buffer.size());

	/*while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}*/

	/*while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		sys.get_messages();
		print_tree(sys.messages_root);
	}*/

 	return 0;
}
