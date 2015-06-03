#include "gameserver.hpp"
#include "gameconnection.hpp"
#include "gameconnectionfactory.hpp"
#include "Poco/Net/TCPServerParams.h"

namespace Botventure{
namespace Network{

GameServer::GameServer() : server(new GameConnectionFactory<Network::GameConnection>(), Defaults::Port, new Poco::Net::TCPServerParams()){
}

void GameServer::Start(){
  server.start();
}

void GameServer::Stop(){
  server.stop();
}


}
}
