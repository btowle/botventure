#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/StreamSocket.h"

namespace Botventure{
namespace Network{

class GameConnection : public Poco::Net::TCPServerConnection
{
public:
	GameConnection(const Poco::Net::StreamSocket& s): TCPServerConnection(s) {}

	void run();
};

}
}
