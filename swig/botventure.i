%module botventure
%{
#ifdef RAKE_COMPILATION
#include "robot.hpp"
#include "gameserver.hpp"
#include "map2d.hpp"
#include "mob.hpp"
#include "position.hpp"
#include "gameconnection.hpp"
#else
#include "src/bot/robot.hpp"
#include "src/network/messages.hpp"
#include "src/network/gameserver.hpp"
#include "src/world/map2d.hpp"
#include "src/world/mob.hpp"
#include "src/world/position.hpp"
#endif //RAKE_COMPILATION

using namespace Botventure;
using namespace World;
using namespace Bot;
using namespace Messages;
%}

%include std_string.i
%include std_vector.i

namespace Botventure{
namespace Messages{
enum Direction{
  NODIRECTION=0,
  UP=1,
  RIGHT=2,
  DOWN=3,
  LEFT=4
};
enum ActionType{
  WAIT=0,
  MOVE=1,
  ATTACK=2
};
enum SensorType{
  INTERNAL=0,
  GPS=1
};
enum NodeType{
  UNKNOWN=0,
  GROUND=1,
  WALL=2,
  GOAL=3
};
}
}

namespace std {
  %template(MobVector) vector<Mob>;
  %template(TerrainVector) vector<NodeType>;
}

%rename("to_s") ToString() const;
%include "src/world/position.hpp"

%predicate IsWalkable(Messages::NodeType t) const;
%include "src/world/mob.hpp"

%rename("to_s") ToString() const;
%rename("to_string") ToString(const std::vector<Mob>& enemies, const Mob& player) const;
%rename("width") GetWidth() const;
%rename("height") GetHeight() const;
%rename("nodes") GetNodes() const;
%rename("node") GetNode(int index) const;
%rename("node") GetNode(int x, int y) const;
%rename("node") GetNode(Position p) const;
%predicate IsInBounds(Position p) const;
%include "src/world/map2d.hpp"

%predicate IsPlaying();
%predicate IsWinner();
%predicate IsConnected();
%rename("turn") GetTurn();
%rename("map") GetMap();
%rename("enemies") GetEnemies();
%rename("player") GetPlayer();
%bang Move(Direction direction);
%bang Attack(Direction direction);
%bang Wait();
%bang Connect();
%bang Disconnect();
%include "src/bot/robot.hpp"

%import "src/network/gameconnection.hpp"

%predicate Disconnected();
%bang Start();
%bang Stop();
%include "src/network/gameserver.hpp"
