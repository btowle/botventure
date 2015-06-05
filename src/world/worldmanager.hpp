#ifndef world_worldmanager_
#define world_worldmanager_

#include "map2d.hpp"
#include "mob.hpp"
#include "position.hpp"

#ifdef RAKE_COMPILATION
#include "messages.hpp"
#else
#include "network/messages.hpp"
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
  Messages::GameState GetGameState(){ return gameState; }

private:
  bool MovePlayer(Position offset);

  Map2D map;
  std::vector<Mob> enemies;
  Mob player;
  Messages::GameState gameState;

};


}
}

#endif
