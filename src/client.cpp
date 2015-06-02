#include "bot/robot.hpp"
#include <iostream>
#include <stdlib.h>
#include "Poco/Exception.h"

using namespace Botventure;

int main(int argc, char* argv[]){
  try
  {
    Bot::Robot bot;
    bot.Connect();
    while(bot.connected){
      std::cout << bot.GetTurn() << std::endl;
      //sense
      World::Map2D map(bot.GetMap());
      World::Mob player(bot.GetPlayer());
      std::vector<World::Mob> enemies(bot.GetEnemies());
      std::cout << map.ToString(enemies, player) << std::endl;
      //move
      if(!bot.Move(Bot::DOWN)){
        std::cout << "I hit a wall, I give up." << std::endl;
        bot.connected = false;
      }
    }
    std::cout << "disconnected from server" << std::endl;
  }
  catch(Poco::TimeoutException const& e)
  {
    std::cerr << "Connection to server timed out." << std::endl;
  }
  catch(Poco::Exception const& e)
  {
    std::cerr << e.displayText() << std::endl;
  }
  catch(std::exception const& e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
}
