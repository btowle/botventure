#ifndef world_mob_
#define world_mob_

#include "position.hpp"

namespace Botventure{
namespace World{

class Mob{
public:
  Mob(Position position=Position(), int health=10) : position(position), health(health){}

  Position position;
  int health;
private:

};

}
}

#endif
