#include "map/map2d.hpp"
#include "network/messagereader.hpp"
#include "network/messages.hpp"
#include "network/defaults.hpp"
#include <iostream>
#include <stdlib.h>
#include "Poco/Exception.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"

using namespace Botventure;

int main(int argc, char* argv[]){
  try
  {
    Poco::Net::SocketAddress address("localhost", Network::Defaults::Port);
    Poco::Net::StreamSocket socket(address);
    Poco::Net::SocketStream sstream(socket);
    Network::MessageReader mReader(sstream);

    Messages::Map mapMessage;

    if(mReader.GetNextMessage() == Messages::Header::MAP){
      Map::Map2D map(mReader.CurrentMessage<Messages::Map>());
  	  std::cout << map.GetWidth() << "," << map.GetHeight() << std::endl;
    }
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
