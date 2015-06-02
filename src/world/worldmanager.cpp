#include "worldmanager.hpp"
#include <iostream>

namespace Botventure{
namespace World{

  WorldManager::WorldManager(){
    try{
      map.Load("../maps/default.map");
    }
    catch(std::exception const& e)
    {
      std::cerr << "Exception:" << e.what() << std::endl;
    }
  }

  const Map2D& WorldManager::GetMap() const{
    return map;
  }
}
}
