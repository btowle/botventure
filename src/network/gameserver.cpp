#include "gameserver.hpp"
#include "gameconnection.hpp"
#include "gameconnectionfactory.hpp"
#include "Poco/Net/TCPServerParams.h"

namespace Botventure{
namespace Network{

GameServer::GameServer() :
  server(new GameConnectionFactory<Network::GameConnection>(worldManager,
                                                            worldManagerMutex),
  Defaults::Port,
  new Poco::Net::TCPServerParams()){
}

void GameServer::Start(){
  server.start();
}

void GameServer::Stop(){
  server.stop();
}

bool GameServer::Disconnected(){
  return server.currentConnections() == 0;
}

GameServer& GameServer::LogLevel(int logLevel){
  ScopedLock lock(worldManagerMutex);
  worldManager.logLevel = logLevel;
  return *this;
}

GameServer& GameServer::TurnLimit(int turnLimit){
  ScopedLock lock(worldManagerMutex);
  worldManager.turnLimit = turnLimit;
  return *this;
}

}
}
