#include "network/gameconnection.hpp"
#include "messages/header.pb.h"
#include <iostream>
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Network{

void GameConnection::run(){
	Poco::Net::StreamSocket& streamsocket = socket();
	Poco::Net::SocketStream sstream(streamsocket);
	try{
		std::cout << "connection recieved" << std::endl;
		Messages::Header header;
		header.set_messagesize(i);
		header.set_messagetype(Messages::Header::NOOP);
		header.SerializeToOstream(&sstream);
	}catch(Poco::Exception& e)
	{
		std::cerr << e.displayText() << std::endl;
	}
}

}
}
