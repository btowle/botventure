#include "mob.hpp"
#include <algorithm>

namespace Botventure{
namespace World{

bool Mob::IsWalkable(Messages::NodeType t) const{
  static std::vector<Messages::NodeType> walkable;
  if(walkable.empty()){
    walkable.push_back(Messages::GROUND);
    walkable.push_back(Messages::GOAL);
  }
  auto iterator = find(walkable.begin(), walkable.end(), t);
  return iterator != walkable.end();
}

Mob& Mob::SetPosition(World::Position position){
  this->position = position;
  return *this;
}
Mob& Mob::SetHealth(int health){
  this->health = health;
  return *this;
}
Mob& Mob::SetArmorClass(int armorClass){
  this->armorClass = armorClass;
  return *this;
}
Mob& Mob::SetAttackStrength(int attackStrength){
  this->attackStrength = attackStrength;
  return *this;
}
Mob& Mob::SetName(std::string name){
  this->name = name;
  return *this;
}
Mob& Mob::SetSymbol(char character){
  this->symbol = character;
  return *this;
}


}
}
