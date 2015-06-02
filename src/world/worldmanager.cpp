#include "worldmanager.hpp"
#include "position.hpp"
#include <iostream>
#include <map>

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

  bool WorldManager::MovePlayer(Messages::ActionRequest::Direction direction){
    static std::map<Messages::ActionRequest::Direction, Position> map;
    if(map.empty()){
      map[Messages::ActionRequest::UP] = Position(0,1);
      map[Messages::ActionRequest::RIGHT] = Position(1,0);
      map[Messages::ActionRequest::DOWN] = Position(0,-1);
      map[Messages::ActionRequest::LEFT] = Position(-1,0);
    }
    return MovePlayer(map[direction]);
  }

  bool WorldManager::MovePlayer(Position offset){
    if(map.InBounds(player.position + offset) &&
       map.GetNode(player.position + offset) == Messages::Map::GROUND){
      for(Mob enemy : enemies){
        if(enemy.position == player.position){
          return false;
        }
      }
      player.position += offset;
      return true;
    }
    return false;
  }
}
}
