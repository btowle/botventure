#ifndef network_gameconnectionfactory_
#define network_gameconnectionfactory_

#include "gameconnection.hpp"

#ifdef RAKE_COMPILATION
#include "map2d.hpp"
#else
#include "world/map2d.hpp"
#endif //RAKE_COMPILATION

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"

namespace Botventure{
namespace Network{

template <class T>
class GameConnectionFactory : public Poco::Net::TCPServerConnectionFactory
{
public:
	//GameConnectionFactory(World::Map2D& map) : map(map){}
  GameConnectionFactory(){}
	~GameConnectionFactory(){}
	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
	{
    return new T(socket);
		//return new T(socket, map);
	}
private:
	//World::Map2D& map;
};

}
}

#endif
