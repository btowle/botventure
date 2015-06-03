#ifndef network_gameserver_
#define network_gameserver_

#include "defaults.hpp"
#include "gameconnection.hpp"
#include "gameconnectionfactory.hpp"
#include "Poco/Net/TCPServerParams.h"

namespace Botventure{
namespace Network{

class GameServer{
public:
  GameServer();
  void Start();
  void Stop();
  bool Disconnected();
private:
  Poco::Net::TCPServer server;
};

}
}


#endif
