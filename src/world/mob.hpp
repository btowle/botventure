#ifndef world_mob_
#define world_mob_

#ifdef RAKE_COMPILATION
#include "messages.hpp"
#else
#include "network/messages.hpp"
#endif //RAKE_COMPILATION
#include "position.hpp"

#include <string>

namespace Botventure{
namespace World{

class Mob{
public:
  Mob(const Mob& mob) : position(mob.position),
                        health(mob.health),
                        armorClass(mob.armorClass),
                        attackStrength(mob.attackStrength),
                        name(mob.name),
                        alive(mob.alive){}
  Mob() : position(Position()){};

  virtual bool IsWalkable(Messages::NodeType t) const;

  Position position;
  int health = 2;

  int armorClass = 10;
  int attackStrength = 1;

  std::string name = "Mob";

  bool alive = true;

  Mob& SetPosition(World::Position position);
  Mob& SetHealth(int health);
  Mob& SetArmorClass(int armorClass);
  Mob& SetAttackStrength(int attackStrength);
  Mob& SetName(std::string name);
private:

};

}
}

#endif
