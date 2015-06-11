#include "position.hpp"
#include <sstream>

namespace Botventure{
namespace World{
  const Position Position::Up = Position(0,1);
  const Position Position::Right = Position(1,0);
  const Position Position::Down = Position(0,-1);
  const Position Position::Left = Position(-1,0);

  bool Position::operator==(const Position& rhs) const{
    return (x == rhs.x) && (y == rhs.y);
  }
  bool Position::operator!=(const Position& rhs) const{
    return !(this->operator==(rhs));
  }

  Position& Position::operator+=(const Position& rhs){
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  const Position Position::operator+(const Position& rhs) const{
    return Position(*this) += rhs;
  }

  Position& Position::operator-=(const Position& rhs){
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  const Position Position::operator-(const Position& rhs) const{
    return Position(*this) -= rhs;
  }

  std::string Position::ToString() const{
    std::stringstream ss;
    ss << x << "," << y;
    return ss.str();
  }

}
}
