#ifndef network_gameconnection_
#define network_gameconnection_

#include "messagereader.hpp"
#include "messagewriter.hpp"

#ifdef RAKE_COMPILATION
#include "worldmanager.hpp"
#else
#include "world/worldmanager.hpp"
#endif //RAKE_COMPILATION

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Mutex.h"

namespace Botventure{
namespace Network{

typedef Poco::ScopedLock<Poco::Mutex> ScopedLock;

class GameConnection : public Poco::Net::TCPServerConnection
{
public:
	GameConnection(const Poco::Net::StreamSocket& s,
                 World::WorldManager& worldManager,
                 Poco::Mutex& worldManagerMutex) : TCPServerConnection(s),
                                                   streamsocket(s),
                                                   sstream(streamsocket),
                                                   mReader(sstream),
                                                   mWriter(sstream),
                                                   worldManager(worldManager),
                                                   worldManagerMutex(worldManagerMutex) {
    streamsocket.setReceiveTimeout(5000000);
    streamsocket.setReceiveTimeout(5000000);
    }

	void run();
private:
  Poco::Net::StreamSocket streamsocket;
  Poco::Net::SocketStream sstream;
  MessageReader mReader;
  MessageWriter mWriter;

  World::WorldManager& worldManager;
  Poco::Mutex& worldManagerMutex;

  int turnNumber;
  bool actedThisTurn;

  void Handshake();
  void InitGame();
  void AdvanceTurn();
  void HandleMessage();
  void HandleSensorRequest();
  void HandleActionRequest();
  void HandleGameInfo();
};

}
}

#endif
