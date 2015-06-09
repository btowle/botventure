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
    return MovePlayer(DirectionOffset(direction));
  }

  bool WorldManager::MovePlayer(Position offset){
    if(map.IsInBounds(player.position + offset) &&
       player.IsWalkable(map.GetNode(player.position + offset))){
      for(Mob& enemy : enemies){
        if(enemy.alive && enemy.position == player.position + offset){
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

  bool WorldManager::Attack(Messages::Direction direction){
    return Attack(player, direction);
  }

  bool WorldManager::Attack(Mob& attacker, Messages::Direction direction){
    return Attack(attacker, AdjacentPosition(attacker.position, direction));
  }

  bool WorldManager::Attack(Mob& attacker, Position position){
    for(Mob& e : enemies){
      if(e.position == position){
        return Attack(attacker, e);
      }
    }
    if(player.position == position){
      return Attack(attacker, player);
    }
    if(logLevel >1){
      std::cout << attacker.name << " attacks nothing." << std::endl;
    }
    return false;
  }

  bool WorldManager::Attack(Mob& attacker, Mob& defender){
    bool log = logLevel > 1;
    if(defender.alive == false){
      if(log){
        std::cout << attacker.name << " attacks " << defender.name <<
                      "'s corpse." << std::endl;
      }
      return false;
    }
    if(&attacker == &defender){
      if(log){
        std::cout << attacker.name <<
                     " tries to attack itself, but can't." << std::endl;
      }
      return false;
    }
    if(Roll::d20() >= defender.armorClass){
      if(log){
        std::cout << attacker.name << " hits " << defender.name << " for " <<
                     attacker.attackStrength << " damage." << std::endl;
      }
      defender.health -= attacker.attackStrength;
      return true;
    }else{
      if(log){
        std::cout << attacker.name << " misses " << defender.name << "." <<
                     std::endl;
      }
      return false;
    }
  }

  Position WorldManager::DirectionOffset(Messages::Direction direction){
    static std::map<Messages::Direction, Position> map;
    if(map.empty()){
      map[Messages::UP] = Position(0,1);
      map[Messages::RIGHT] = Position(1,0);
      map[Messages::DOWN] = Position(0,-1);
      map[Messages::LEFT] = Position(-1,0);
    }
    return map[direction];
  }

  Position WorldManager::AdjacentPosition(Position position,
                                          Messages::Direction direction){
    return position + DirectionOffset(direction);
  }

  void WorldManager::AdvanceTurn(){
    ++turnNumber;
    SimulateWorld();
    OutputState();
    if(turnLimit > 0 && turnNumber > turnLimit){
      gameState = Messages::FAILURE;
    }
  }

  void WorldManager::InitWorld(){
    map.Load("default.map");
    for(Position p : map.enemySpawns){
      enemies.push_back(Mob()
                        .SetPosition(p)
                        .SetHealth(2)
                        .SetArmorClass(5)
                        .SetAttackStrength(1)
                        .SetName("Goblin"));
    }
    player = Mob()
              .SetPosition(map.playerSpawn)
              .SetHealth(10)
              .SetArmorClass(10)
              .SetAttackStrength(1)
              .SetName("Player");
    gameState = Messages::PLAYING;
    OutputState();
  }

  void WorldManager::SimulateWorld(){
    bool logActions = logLevel > 1;

    if(logLevel > 2){
      std::cout << "Simulating World: " << std::endl;
    }

    for(Mob& e : enemies){
      if(e.alive){
        if(e.health <= 0){
          if(logActions){
            std::cout << e.name << " dies." << std::endl;
          }
          e.alive = false;
          //Score++ for killing monster
        }else{
          //TODO: Mob actions here
        }
      }
    }

    if(player.health <= 0){
      if(logActions){
        std::cout << "Player dies." << std::endl;
      }
      gameState = Messages::FAILURE;
    }
  }

  void WorldManager::OutputState(){
    if(logLevel > 0){
      std::cout << "Turn: " << turnNumber << std::endl;
      std::cout << map.ToString(enemies, player) << std::endl;
    }
  }
}
}
