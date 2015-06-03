%module botventure
%include std_string.i

%{
#include "src/bot/robot.hpp"
#include "src/network/gameserver.hpp"
using namespace Botventure;
using namespace World;
%}

%include std_vector.i
namespace std {
  %template(Vectormob) vector<Botventure::World::Mob>;
}

%include "src/world/mob.hpp"
%include "src/world/map2d.hpp"
%include "src/bot/robot.hpp"

%import "src/network/gameconnection.hpp"
%include "src/network/gameserver.hpp"

//Redefine constants so comparisons work in ruby
%constant const Botventure::Bot::Direction NODIRECTION = Bot::NODIRECTION;
%constant const Botventure::Bot::Direction UP = Bot::UP;
%constant const Botventure::Bot::Direction RIGHT = Bot::RIGHT;
%constant const Botventure::Bot::Direction DOWN = Bot::DOWN;
%constant const Botventure::Bot::Direction LEFT = Bot::LEFT;
