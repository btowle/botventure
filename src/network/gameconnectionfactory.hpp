#ifndef network_gameconnectionfactory_
#define network_gameconnectionfactory_

#include "../world/map2d.hpp"
#include "gameconnection.hpp"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"

namespace Botventure{
namespace Network{

template <class T>
class GameConnectionFactory : public Poco::Net::TCPServerConnectionFactory
{
public:
	GameConnectionFactory(World::Map2D& map) : map(map){}
	~GameConnectionFactory(){}
	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
	{
		return new T(socket, map);
	}
private:
	World::Map2D& map;
};

}
}

#endif
