#include "network/defaults.hpp"
#include <iostream>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"

using namespace Botventure;

int main(int argc, char* argv[]){
	Poco::Net::SocketAddress address("localhost", Network::Defaults::Port);
	Poco::Net::StreamSocket socket(address);
	char buffer[256] = {0};
	int n = socket.receiveBytes(buffer, sizeof(buffer));
	std::cout << std::string(buffer, n) << std::endl;
}
