#ifndef world_position_
#define world_position_

namespace Botventure{
namespace World{

class Position{
public:
  Position(){}
  Position(int x, int y) : x(x), y(y) {}

  bool operator==(const Position& other) const;
  bool operator!=(const Position& other) const;

  Position& operator+=(const Position& rhs);
  const Position operator+(const Position& rhs) const;

  Position& operator-=(const Position& rhs);
  const Position operator-(const Position& rhs) const;

  int x;
  int y;
private:

};


}
}

#endif
