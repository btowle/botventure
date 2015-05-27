#include "network/defaults.hpp"
#include "messages/header.pb.h"
#include <iostream>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"

using namespace Botventure;

int main(int argc, char* argv[]){
	Poco::Net::SocketAddress address("localhost", Network::Defaults::Port);
	Poco::Net::StreamSocket socket(address);
	Poco::Net::SocketStream sstream(socket);
	Messages::Header header;
	header.ParseFromIstream(&sstream);
	if(header.messagetype() == Messages::Header::NOOP)
	{
		std::cout << "noop recieved" << std::endl;
	}
	std::cout << "messagesize = " << header.messagesize() << std::endl;
}
