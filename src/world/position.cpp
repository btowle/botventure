#include "position.hpp"

namespace Botventure{
namespace World{

  bool Position::operator==(const Position& rhs) const{
    return (x == rhs.x) && (y == rhs.y);
  }
  bool Position::operator!=(const Position& rhs) const{
    return !(this->operator==(rhs));
  }

}
}
