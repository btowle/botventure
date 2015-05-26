#include "network/gameconnection.hpp"
#include <iostream>

namespace Botventure{
namespace Network{

void GameConnection::run(){
	Poco::Net::StreamSocket& streamsocket = socket();
	try{
		std::cout << "connection recieved" << std::endl;
		std::string string("hello world");
		streamsocket.sendBytes(string.data(), string.size());
	}catch(Poco::Exception& e)
	{
		std::cerr << e.displayText() << std::endl;
	}
}

}
}
