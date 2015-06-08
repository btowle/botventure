#include "worldmanager.hpp"
#include "position.hpp"
#include <iostream>
#include <map>

namespace Botventure{
namespace World{

  WorldManager::WorldManager(){
    try{
      InitWorld();
      if(logLevel > 2){
        std::cout << "World Started" << std::endl;
      }
    }
    catch(std::exception const& e)
    {
      std::cerr << "Exception:" << e.what() << std::endl;
    }
  }

  const Map2D& WorldManager::GetMap() const{
    if(logLevel > 1){
      std::cout << "Player looks around at the world" << std::endl;
    }
    return map;
  }

  const std::vector<Mob>& WorldManager::GetEnemies() const{
    if(logLevel > 1){
      std::cout << "Player looks for danger" << std::endl;
    }
    return enemies;
  }

  const Mob& WorldManager::GetPlayer() const{
    if(logLevel > 1){
      std::cout << "Player takes personal status" << std::endl;
    }
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
          if(logLevel > 1){
            std::cout << "Player move blocked by enemy." << std::endl;
          }
          return false;
        }
      }
      player.position += offset;
      if(map.GetNode(player.position) == Messages::GOAL){
        gameState = Messages::SUCCESS;
      }
      if(logLevel > 1){
        std::cout << "Player moved to " << player.position.ToString() << std::endl;
      }
      return true;
    }
    if(logLevel > 1){
        std::cout << "Player movement blocked" << std::endl;
    }
    return false;
  }

  void WorldManager::AdvanceTurn(){
    ++turnNumber;
    SimulateWorld();
    OutputState();
  }

  void WorldManager::InitWorld(){
    map.Load("default.map");
    for(Position p : map.enemySpawns){
      enemies.push_back(Mob(p));
    }
    player = Mob(map.playerSpawn);
    gameState = Messages::PLAYING;
    OutputState();
  }

  void WorldManager::SimulateWorld(){

  }

  void WorldManager::OutputState(){
    if(logLevel > 0){
      std::cout << "Turn: " << turnNumber << std::endl;
      std::cout << map.ToString(enemies, player) << std::endl;
    }
  }
}
}
