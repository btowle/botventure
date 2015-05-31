#include "map/map2d.hpp"
#include "network/messagereader.hpp"
#include "network/messagewriter.hpp"
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
    socket.setReceiveTimeout(5000000);
    socket.setSendTimeout(5000000);
    Poco::Net::SocketStream sstream(socket);
    Network::MessageReader mReader(sstream);
    Network::MessageWriter mWriter(sstream);

    //HANDSHAKE
    mWriter.SendHandshake(Messages::Handshake::SYN);
    if(!mReader.GetNextMessage() ||
       mReader.CurrentMessageType() != Messages::Header::HANDSHAKE ||
       mReader.CurrentMessage<Messages::Handshake>().step() != Messages::Handshake::ACK)
    {
      std::cout << mReader.CurrentMessage<Messages::Handshake>().step() << std::endl << std::flush;
      throw std::runtime_error("Server did not properly respond to handshake.");
    }
    mWriter.SendHandshake(Messages::Handshake::NEWGAME);
    //HANDSHAKECOMPLETE

    while(mReader.GetNextMessage()){
      //if(mReader.CurrentMessageType() == Messages::Header::MAP){
      //  Map::Map2D map(mReader.CurrentMessage<Messages::Map>());
    	//  std::cout << map.GetWidth() << "," << map.GetHeight() << std::endl << std::flush;
      //}
    }
    std::cout << "disconnected from server" << std::endl;
  }
  catch(Poco::TimeoutException const& e)
  {
    std::cerr << "Connection to server timed out." << std::endl;
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
