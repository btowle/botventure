#ifndef network_gameconnection_
#define network_gameconnection_

#include "../map/map2d.hpp"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

namespace Botventure{
namespace Network{

class GameConnection : public Poco::Net::TCPServerConnection
{
public:
	GameConnection(const Poco::Net::StreamSocket& s, Map::Map2D& map): TCPServerConnection(s), map(map) {}

	void run();
private:
	Map::Map2D& map;
};

}
}

#endif
