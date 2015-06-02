#ifndef world_worldmanager_
#define world_worldmanager_

#include "map2d.hpp"
#include "mob.hpp"
#include "position.hpp"
#include <vector>

namespace Botventure{
namespace World{

class WorldManager{
public:
  WorldManager();
  const Map2D& GetMap() const;
  const std::vector<Mob>& GetEnemies() const;
  const Mob& GetPlayer() const;

private:
  Map2D map;
  std::vector<Mob> enemies;
  Mob player;

};


}
}

#endif
