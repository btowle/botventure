#ifndef network_gameserver_
#define network_gameserver_

#include "defaults.hpp"
#include "gameconnection.hpp"
#include "gameconnectionfactory.hpp"

#ifdef RAKE_COMPILATION
#include "worldmanager.hpp"
#else
#include "world/worldmanager.hpp"
#endif //RAKE_COMPILATION

#include "Poco/Net/TCPServerParams.h"
#include "Poco/Mutex.h"

namespace Botventure{
namespace Network{

typedef Poco::ScopedLock<Poco::Mutex> ScopedLock;

class GameServer{
public:
  GameServer();
  void Start();
  void Stop();
  bool Disconnected();

  GameServer& LogLevel(int logLevel);
  GameServer& TurnLimit(int turnLimit);
private:
  Poco::Net::TCPServer server;
  World::WorldManager worldManager;
  Poco::Mutex worldManagerMutex;
};

}
}


#endif
