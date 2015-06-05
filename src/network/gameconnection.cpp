#include "gameconnection.hpp"
#include "messages.hpp"
#include "messagereader.hpp"
#include "messagewriter.hpp"
#include <iostream>
#include "Poco/Net/SocketStream.h"
#include "Poco/ScopedLock.h"

#include <stdlib.h>

namespace Botventure{
namespace Network{

void GameConnection::run(){
	try
	{
    Handshake();
    InitGame();

    //Simulate world here

    while(mReader.GetNextMessage()){
      Poco::ScopedLock<Poco::Mutex> lock(worldManagerMutex);
      if(worldManager.GetGameState() != Messages::PLAYING){
        break;
      }

      HandleMessage();
      if(actedThisTurn){
        AdvanceTurn();
      }
    }

    Poco::ScopedLock<Poco::Mutex> lock(worldManagerMutex);
    if(worldManager.GetGameState() == Messages::PLAYING){
      std::cout << "Client disconnected." << std::endl;
    }else{
      std::cout << "The game is over!" << std::endl;
    }
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
      mReader.CurrentMessageType() != Messages::HANDSHAKE ||
      mReader.CurrentMessage<Messages::Handshake>().step() != Messages::SYN){
      throw std::runtime_error("Connection received without valid handshake.1");
    }
    mWriter.SendHandshake(Messages::ACK);
    if(!mReader.GetNextMessage() ||
      mReader.CurrentMessageType() != Messages::HANDSHAKE ||
      mReader.CurrentMessage<Messages::Handshake>().step() != Messages::NEWGAME){
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
    mWriter.SendGameInfo(++turnNumber, worldManager.GetGameState());
}

void GameConnection::HandleMessage(){
      Messages::MessageType msgType = mReader.CurrentMessageType();
      switch(mReader.CurrentMessageType()){
        case Messages::SENSORREQUEST:
          HandleSensorRequest();
          break;
        case Messages::ACTIONREQUEST:
          HandleActionRequest();
          break;
        case Messages::GAMEINFO:
          HandleGameInfo();
          break;
        case Messages::SENSORRESPONSE:
        case Messages::ACTIONRESPONSE:
        case Messages::HANDSHAKE:
        case Messages::MESSAGEERROR:
        default:
          std::cerr << "Innapropriate message received." << mReader.CurrentMessageType() << std::endl;
          break;
      }

}
void GameConnection::HandleSensorRequest(){
  switch(mReader.CurrentMessage<Messages::SensorRequest>().sensor_type()){
    case Messages::INTERNAL:
      //TODO: internal sensor sending
      //mWriter.SendSensorResponse();
      break;
    case Messages::GPS:
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
    case Messages::MOVE:
      std::cout << "Handling Move Request" << std::endl << std::flush;
      mWriter.SendActionResponse(worldManager.MovePlayer(msg.direction()));
      break;
    case Messages::ATTACK:
      mWriter.SendActionResponse(false);
      break;
    case Messages::WAIT:
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
