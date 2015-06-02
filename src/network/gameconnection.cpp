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
    Handshake();
    InitGame();

    while(mReader.GetNextMessage()){
      HandleMessage();
      if(actedThisTurn){
        AdvanceTurn();
      }
    }

    std::cout << "Client disconnected." << std::endl;
    std::cout << "Server thread exiting..." << std::endl;
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

void GameConnection::Handshake(){
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
}

void GameConnection::InitGame(){
    turnNumber = 0;
    AdvanceTurn();
}

void GameConnection::AdvanceTurn(){
    actedThisTurn = false;
    mWriter.SendGameInfo(++turnNumber);
}

void GameConnection::HandleMessage(){
      Messages::Header::MessageType msgType = mReader.CurrentMessageType();
      switch(mReader.CurrentMessageType()){
        case Messages::Header::SENSORREQUEST:
          HandleSensorRequest();
          break;
        case Messages::Header::ACTIONREQUEST:
          HandleActionRequest();
          break;
        case Messages::Header::GAMEINFO:
          HandleGameInfo();
          break;
        case Messages::Header::SENSORRESPONSE:
        case Messages::Header::ACTIONRESPONSE:
        case Messages::Header::HANDSHAKE:
        case Messages::Header::ERROR:
        default:
          std::cerr << "Innapropriate message received." << mReader.CurrentMessageType() << std::endl;
          break;
      }

}
void GameConnection::HandleSensorRequest(){
  switch(mReader.CurrentMessage<Messages::SensorRequest>().sensor_type()){
    case Messages::BotStatus::INTERNAL:
      //TODO: internal sensor sending
      //mWriter.SendSensorResponse();
      break;
    case Messages::BotStatus::GPS:
      std::cout << "Handling GPS Request" << std::endl << std::flush;
      mWriter.SendSensorResponse(worldManager.GetMap(), worldManager.GetEnemies(), worldManager.GetPlayer());
      break;
  }
  //.map
  //.enemies
  //.bot_status
    //.health
    //.available_sensors
}
void GameConnection::HandleActionRequest(){
  actedThisTurn = true;
  Messages::ActionRequest msg = mReader.CurrentMessage<Messages::ActionRequest>();
  switch(msg.action_type()){
    case Messages::ActionRequest::MOVE:
      std::cout << "Handling Move Request" << std::endl << std::flush;
      mWriter.SendActionResponse(worldManager.MovePlayer(msg.direction()));
      break;
    case Messages::ActionRequest::ATTACK:
      mWriter.SendActionResponse(false);
      break;
    case Messages::ActionRequest::WAIT:
      mWriter.SendActionResponse(true);
      break;
    default:
      mWriter.SendActionResponse(false);
      break;
  }
}
void GameConnection::HandleGameInfo(){
  //TODO: make gameinfo.proto contain info for start/restart/cleandisconnect/etc
  //which will be handled here.
}

}
}
