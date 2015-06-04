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


}
}
