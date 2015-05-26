#include "network/defaults.hpp"
#include "network/gameconnection.hpp"
#include <iostream>

using namespace Botventure;

int main(int argc, char* argv[]){
	Poco::Net::TCPServer server(new Poco::Net::TCPServerConnectionFactoryImpl<Network::GameConnection>(), Network::Defaults::Port);
	server.start();
	
	std::string input;
	while(std::cin >> input){
		if(input.compare("exit\n")){
			std::cout << "Shutting down server" << std::endl;
			break;
		}
	}
}
