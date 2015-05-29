#include "gameconnection.hpp"
#include "messages.hpp"
#include <iostream>
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Network{

void GameConnection::run(){
	try
	{
	  Poco::Net::StreamSocket& streamsocket = socket();
  	Poco::Net::SocketStream sstream(streamsocket);

		std::cout << "connection recieved" << std::endl;
		Messages::Header header;
		Messages::Map mapMessage;

		map.SendMap(sstream);
	}
	catch(Poco::Exception const& e)
	{
		std::cerr << e.displayText() << std::endl;
	}
  catch(std::exception const& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}

}
}
