#include "network/gameserver.hpp"
//#include "world/map2d.hpp"
//#include "network/defaults.hpp"
//#include "network/gameconnection.hpp"
//#include "network/gameconnectionfactory.hpp"
#include <iostream>
#include <string>
//#include "Poco/Net/TCPServerParams.h"

using namespace Botventure;

int main(int argc, char* argv[]){
  Network::GameServer gameServer;

  gameServer.Start();

	std::string input;
	while(std::cin >> input){
		if(input.compare("exit") == 0){
			std::cout << "Shutting down server" << std::endl;
			break;
		}
	}

  gameServer.Stop();
}
