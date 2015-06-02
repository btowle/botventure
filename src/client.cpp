#include "network/messagereader.hpp"
#include "network/messagewriter.hpp"
#include "network/messages.hpp"
#include "network/defaults.hpp"
#include "world/map2d.hpp"
#include "world/mob.hpp"
#include "world/position.hpp"
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


    while(mReader.GetNextMessage() &&
          mReader.CurrentMessageType() == Messages::Header::GAMEINFO){
      // get turn number
      std::cout << "TURN " << mReader.CurrentMessage<Messages::GameInfo>().turn_number() << std::endl;

      //MAP REQUEST
      mWriter.SendSensorRequest(Messages::BotStatus::GPS);
      if(!mReader.GetNextMessage() ||
          mReader.CurrentMessageType() != Messages::Header::SENSORRESPONSE ||
          mReader.CurrentMessage<Messages::SensorResponse>().sensor_type() != Messages::BotStatus::GPS){
        throw std::runtime_error("Server did not response appropriately to SensorRequest");
      }
      Messages::SensorResponse msg = mReader.CurrentMessage<Messages::SensorResponse>();
      Messages::Map map = msg.map();
      World::Map2D worldMap(map);

      std::vector<World::Mob> enemies;
      for(int i=0; i<msg.enemies_size(); ++i){
        Messages::Enemy e = msg.enemies(i);
        enemies.push_back(World::Mob(World::Position(e.x(), e.y()), e.health()));
      }

      Messages::BotStatus b = msg.bot_status();
      World::Mob player(World::Position(b.x(), b.y()), b.health());

      std::cout << worldMap.ToString(enemies, player) << std::endl;
      //MAP REQUEST COMPLETE

      //MOVE REQUEST
      //send move request
      mWriter.SendActionRequest(Messages::ActionRequest::MOVE, Messages::ActionRequest::DOWN);
      //get move response
      if(!mReader.GetNextMessage() ||
          mReader.CurrentMessageType() != Messages::Header::ACTIONRESPONSE){
        throw std::runtime_error("Server did not response appropriately to ActionRequest");
      }
      if(mReader.CurrentMessage<Messages::ActionResponse>().result() == false){
        std::cout << "I hit a wall, I give up" << std::endl;
        break;
      }
      //MOVE REQUEST OVER
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
