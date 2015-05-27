#include "network/defaults.hpp"
#include "network/gameconnection.hpp"
#include "network/gameconnectionfactory.hpp"
#include <iostream>

using namespace Botventure;

int main(int argc, char* argv[]){
	int i = 6;
	
	Poco::Net::TCPServer server(new Network::GameConnectionFactory<Network::GameConnection>(i), Network::Defaults::Port);
	server.start();
	
	std::string input;
	while(std::cin >> input){
		if(input.compare("exit\n")){
			std::cout << "Shutting down server" << std::endl;
			break;
		}
	}
}
