#ifndef world_worldmanager_
#define world_worldmanager_

#include "map2d.hpp"
#include "mob.hpp"
#include "position.hpp"

#ifdef RAKE_COMPILATION
#include "messages.hpp"
#include "roll.hpp"
#else
#include "network/messages.hpp"
#include "roll/roll.hpp"
#endif //RAKE_COMPILATION

#include <vector>

namespace Botventure{
namespace World{

class WorldManager{
public:
  WorldManager();
  const Map2D& GetMap() const;
  const std::vector<Mob>& GetEnemies() const;
  const Mob& GetPlayer() const;

  bool MovePlayer(Messages::Direction direction);
  bool Attack(Messages::Direction direction);
  bool Attack(Mob& attacker, Messages::Direction direction);
  bool Attack(Mob& attacker, Position position);
  Messages::GameState GetGameState(){ return gameState; }

  int GetTurn(){ return turnNumber; }
  void AdvanceTurn();

  int logLevel = 0;
  int turnLimit = -1;

private:
  bool MovePlayer(Position offset);
  bool Attack(Mob& attacker, Mob& defender);

  Position DirectionOffset(Messages::Direction direction);
  Position AdjacentPosition(Position position, Messages::Direction direction);

  void InitWorld();
  void SimulateWorld();

  void OutputState();

  Map2D map;
  std::vector<Mob> enemies;
  Mob player;
  Messages::GameState gameState;
  int turnNumber = 0;
};


}
}

#endif
