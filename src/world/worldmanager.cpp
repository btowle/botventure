#include "worldmanager.hpp"
#include <iostream>

namespace Botventure{
namespace World{

  WorldManager::WorldManager(){
    try{
      map.Load("../maps/default.map");
      for(Position p : map.enemySpawns){
        enemies.push_back(Mob(p));
      }
      player = Mob(map.playerSpawn);
    }
    catch(std::exception const& e)
    {
      std::cerr << "Exception:" << e.what() << std::endl;
    }
  }

  const Map2D& WorldManager::GetMap() const{
    return map;
  }

  const std::vector<Mob>& WorldManager::GetEnemies() const{
    return enemies;
  }

  const Mob& WorldManager::GetPlayer() const{
    return player;
  }
}
}
