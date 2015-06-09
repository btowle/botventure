#ifndef bot_robot_
#define bot_robot_

#ifdef RAKE_COMPILATION
#include "defaults.hpp"
#include "messagereader.hpp"
#include "messagewriter.hpp"
#include "map2d.hpp"
#include "mob.hpp"
#else
#include "network/defaults.hpp"
#include "network/messagereader.hpp"
#include "network/messagewriter.hpp"
#include "world/map2d.hpp"
#include "world/mob.hpp"
#endif //RAKE_COMPILATION

#include <string>
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Bot{

typedef Messages::Direction Direction;

class Robot{
public:
  Robot() : address("localhost", Network::Defaults::Port),
            socket(address), sstream(socket),
            mReader(sstream), mWriter(sstream){
    socket.setReceiveTimeout(5000000);
    socket.setSendTimeout(5000000);
  }

  bool Connect();
  bool Disconnect();
  bool IsConnected();
  bool IsPlaying();
  bool IsWinner();

  int GetTurn();
  World::Map2D GetMap();
  std::vector<World::Mob> GetEnemies();
  World::Mob GetPlayer();
  
  bool Move(Direction direction);
  bool Attack(Direction direction);
  bool Wait();
  
private:
  bool DoAction(Messages::ActionType actionType, Direction direction);

  bool RequestMap();
  bool GetNextTurn();

  Poco::Net::SocketAddress address;
  Poco::Net::StreamSocket socket;
  Poco::Net::SocketStream sstream;
  Network::MessageReader mReader;
  Network::MessageWriter mWriter;

  int currentTurn = 0;
  bool playing = true;
  bool winner = false;
  bool connected = false;

  int mapTurn = -1;
  World::Map2D map;
  int enemiesTurn = -1;
  std::vector<World::Mob> enemies;
  int playerTurn = -1;
  World::Mob player;
};

}
}


#endif
