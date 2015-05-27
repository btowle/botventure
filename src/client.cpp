#include "map/map2d.hpp"
#include "messages/header.pb.h"
#include "messages/map.pb.h"
#include "network/defaults.hpp"
#include <iostream>
#include <stdlib.h>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"

using namespace Botventure;

int main(int argc, char* argv[]){
	Poco::Net::SocketAddress address("localhost", Network::Defaults::Port);
	Poco::Net::StreamSocket socket(address);
	Poco::Net::SocketStream sstream(socket);
	Messages::Header header;
	Messages::Map mapMessage;

	char* buffer = new char[256];
	int headersize;

	sstream >> headersize;
	sstream.read(buffer, headersize);

	if(!header.ParseFromArray(buffer, headersize)) {
		std::cerr << "did not receive header, exiting" << std::endl << std::flush;
		exit(EXIT_FAILURE);
	}
	else if(header.messagetype() == Messages::Header::MAP) {
		sstream.read(buffer, header.messagelength());
		if(!mapMessage.ParseFromArray(buffer, header.messagelength())){
			std::cerr << "did not receive mapMessage, exiting" << std::endl << std::flush;
			exit(EXIT_FAILURE);
		}
	}
	Map::Map2D map(mapMessage);
	std::cout << map.GetWidth() << "," << map.GetHeight() << std::endl;
}
