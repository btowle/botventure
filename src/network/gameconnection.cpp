#include "gameconnection.hpp"
#include "messages.hpp"
#include "messagereader.hpp"
#include "messagewriter.hpp"
#include <iostream>
#include "Poco/Net/SocketStream.h"

#include <stdlib.h>

namespace Botventure{
namespace Network{

void GameConnection::run(){
	try
	{
	  Poco::Net::StreamSocket& streamsocket = socket();
    streamsocket.setReceiveTimeout(5000000);
    streamsocket.setSendTimeout(5000000);
  	Poco::Net::SocketStream sstream(streamsocket);
    MessageReader mReader(sstream);
    MessageWriter mWriter(sstream);

    //HANDSHAKE
    if(!mReader.GetNextMessage() ||
      mReader.CurrentMessageType() != Messages::Header::HANDSHAKE ||
      mReader.CurrentMessage<Messages::Handshake>().step() != Messages::Handshake::SYN){
      throw std::runtime_error("Connection received without valid handshake.1");
    }
    mWriter.SendHandshake(Messages::Handshake::ACK);
    if(!mReader.GetNextMessage() ||
      mReader.CurrentMessageType() != Messages::Header::HANDSHAKE ||
      mReader.CurrentMessage<Messages::Handshake>().step() != Messages::Handshake::NEWGAME){
      throw std::runtime_error("Connection received without valid handshake.2");
    }
    std::cout << "connection received, new game" << std::endl;
    //HANDSHAKE COMPLETE

    //init game
    //send turn 0 start
    while(mReader.GetNextMessage()){
      //if sensor
        //reply
      //if action
        //reply
        //simulate
        //send turn++
      //mWriter.SendMap(map);
      sleep(4);
    }
	}
  catch(Poco::TimeoutException const& e)
  {
    std::cout << "Client disconnected due to timeout." << std::endl;
    std::cout << "Server thread exiting..." << std::endl;
  }
	catch(Poco::Exception const& e)
	{
		std::cerr << "Poco: " << e.displayText() << std::endl;
	}
  catch(std::exception const& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}

}
}
