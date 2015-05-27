#ifndef network_gameconnection_
#define network_gameconnection_

#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

namespace Botventure{
namespace Network{

class GameConnection : public Poco::Net::TCPServerConnection
{
public:
	GameConnection(const Poco::Net::StreamSocket& s, int& i): TCPServerConnection(s), i(i) {}

	void run();
private:
	int& i;
};

}
}

#endif