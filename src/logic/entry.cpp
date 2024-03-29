// debug entry point

#include "message_system.hpp"

int main(int argc, char* argv[])
{
	MessageSystem sys;

	int ret = sys.connect_client();
	if(ret != 0){
		std::cerr << "Client se nemohl pripojit.\n";
		return 1;
	}

	sys.add_topic("t1");
	sys.add_topic("t2/sub1");

	while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	/*while(true){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		sys.get_messages();
		print_tree(sys.messages_root);
	}*/

 	return 0;
}
