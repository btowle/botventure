#ifndef network_gameconnection_
#define network_gameconnection_

#include "messagereader.hpp"
#include "messagewriter.hpp"
#include "../world/map2d.hpp"
#include "../world/worldmanager.hpp"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

namespace Botventure{
namespace Network{

class GameConnection : public Poco::Net::TCPServerConnection
{
public:
	GameConnection(const Poco::Net::StreamSocket& s, World::Map2D& map): TCPServerConnection(s), streamsocket(s), sstream(streamsocket), mReader(sstream), mWriter(sstream), map(map) {
    streamsocket.setReceiveTimeout(5000000);
    streamsocket.setReceiveTimeout(5000000);
    }

	void run();
private:
  Poco::Net::StreamSocket streamsocket;
  Poco::Net::SocketStream sstream;
  MessageReader mReader;
  MessageWriter mWriter;

  World::WorldManager worldManager;
	World::Map2D& map;
  int turnNumber;

  void Handshake();
  void InitGame();
  void HandleMessage();
  void HandleSensorRequest();
  void HandleActionRequest();
  void HandleGameInfo();
};

}
}

#endif
