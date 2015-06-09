#include "roll.hpp"

namespace Botventure{
namespace Roll{

  std::mt19937& rng(){
    static std::random_device rd;
    static std::mt19937 rng(rd());
    return rng;
  }

  int d20(){
    static std::uniform_int_distribution<> d{};
    return d(rng(), decltype(d)::param_type(1,20));
  }

}
}
