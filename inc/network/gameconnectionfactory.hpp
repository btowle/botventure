#ifndef network_gameconnectionfactory_
#define network_gameconnectionfactory_

#include "network/gameconnection.hpp"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"

namespace Botventure{
namespace Network{

template <class T>
class GameConnectionFactory : public Poco::Net::TCPServerConnectionFactory
{
public:
	GameConnectionFactory(int& i) : i(i){}
	~GameConnectionFactory(){}
	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
	{
		return new T(socket, i);
	}
private:
	int& i;
};

}
}

#endif