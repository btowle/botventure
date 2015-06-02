%module botventure
%include std_string.i

%{
#include "src/bot/robot.hpp"
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
