#ifndef world_mob_
#define world_mob_

#include "../network/messages.hpp"
#include "position.hpp"

namespace Botventure{
namespace World{

class Mob{
public:
  Mob(const Mob& mob) : position(mob.position), health(mob.health){}
  Mob(Position position=Position(), int health=10) : position(position), health(health){}

  virtual bool IsWalkable(Messages::NodeType t);

  Position position;
  int health;
private:

};

}
}

#endif
