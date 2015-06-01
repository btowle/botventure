#include "world/map2d.hpp"
#include "network/defaults.hpp"
#include "network/gameconnection.hpp"
#include "network/gameconnectionfactory.hpp"
#include <iostream>
#include "Poco/Net/TCPServerParams.h"

using namespace Botventure;

int main(int argc, char* argv[]){
	World::Map2D map(10,10);
	
  Poco::Net::TCPServerParams* params = new Poco::Net::TCPServerParams();
  params->setMaxThreads(1);

	Poco::Net::TCPServer server(new Network::GameConnectionFactory<Network::GameConnection>(map), Network::Defaults::Port, params);
	server.start();
	
	std::string input;
	while(std::cin >> input){
		if(input.compare("exit") == 0){
			std::cout << "Shutting down server" << std::endl;
			break;
		}
	}
  server.stop();
}
