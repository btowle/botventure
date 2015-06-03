#include "mob.hpp"
#include <algorithm>

namespace Botventure{
namespace World{

bool Mob::IsWalkable(Messages::Map::NodeType t){
  static std::vector<Messages::Map::NodeType> walkable;
  if(walkable.empty()){
    walkable.push_back(Messages::Map::GROUND);
    walkable.push_back(Messages::Map::GOAL);
  }
  auto iterator = find(walkable.begin(), walkable.end(), t);
  return iterator != walkable.end();
}


}
}
