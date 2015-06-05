#ifndef world_mob_
#define world_mob_

#ifdef RAKE_COMPILATION
#include "messages.hpp"
#else
#include "network/messages.hpp"
#endif //RAKE_COMPILATION
#include "position.hpp"

namespace Botventure{
namespace World{

class Mob{
public:
  Mob(const Mob& mob) : position(mob.position), health(mob.health){}
  Mob(Position position=Position(), int health=10) : position(position), health(health){}

  virtual bool IsWalkable(Messages::NodeType t) const;

  Position position;
  int health;
private:

};

}
}

#endif
