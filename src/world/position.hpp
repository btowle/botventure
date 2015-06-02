#ifndef world_position_
#define world_position_

namespace Botventure{
namespace World{

class Position{
public:
  Position(){}
  Position(int x, int y) : x(x), y(y) {}

  int x;
  int y;
private:

};

}
}

#endif
