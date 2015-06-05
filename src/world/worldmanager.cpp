#include "worldmanager.hpp"
#include "position.hpp"
#include <iostream>
#include <map>

namespace Botventure{
namespace World{

  WorldManager::WorldManager(){
    try{
      map.Load("../data/maps/default.map");
      for(Position p : map.enemySpawns){
        enemies.push_back(Mob(p));
      }
      player = Mob(map.playerSpawn);
      gameState = Messages::PLAYING;
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

  bool WorldManager::MovePlayer(Messages::Direction direction){
    static std::map<Messages::Direction, Position> map;
    if(map.empty()){
      map[Messages::UP] = Position(0,1);
      map[Messages::RIGHT] = Position(1,0);
      map[Messages::DOWN] = Position(0,-1);
      map[Messages::LEFT] = Position(-1,0);
    }
    return MovePlayer(map[direction]);
  }

  bool WorldManager::MovePlayer(Position offset){
    if(map.IsInBounds(player.position + offset) &&
       player.IsWalkable(map.GetNode(player.position + offset))){
      for(Mob enemy : enemies){
        if(enemy.position == player.position){
          return false;
        }
      }
      player.position += offset;
      if(map.GetNode(player.position) == Messages::GOAL){
        gameState = Messages::SUCCESS;
      }
      return true;
    }
    return false;
  }
}
}
