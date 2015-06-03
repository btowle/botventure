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

%constant const Botventure::Bot::Direction NONE = Messages::ActionRequest::NONE;
%constant const Botventure::Bot::Direction UP = Messages::ActionRequest::UP;
%constant const Botventure::Bot::Direction RIGHT = Messages::ActionRequest::RIGHT;
%constant const Botventure::Bot::Direction DOWN = Messages::ActionRequest::DOWN;
%constant const Botventure::Bot::Direction LEFT = Messages::ActionRequest::LEFT;
