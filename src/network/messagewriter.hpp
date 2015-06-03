#ifndef network_messagewriter_
#define network_messagewriter_

#include "messages.hpp"
#include "../world/map2d.hpp"
#include "../world/mob.hpp"
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Network{

class MessageWriter
{
public:
  MessageWriter(Poco::Net::SocketStream& sstream) : sstream(sstream) {}
  ~MessageWriter() {}

  void SendMessage(const Messages::Header& msg) const;
  //void SendMap(const World::Map2D& map);
  void SendActionRequest(Messages::ActionType type, Messages::Direction direction=Messages::NODIRECTION);
  void SendActionResponse(bool result);
  void SendGameInfo(int turnNumber, Messages::GameState gameState);
  void SendHandshake(Messages::Step step);
  void SendSensorRequest(Messages::SensorType sensor);
  void SendSensorResponse(const World::Map2D& map);
  void SendSensorResponse(const World::Map2D& map, const std::vector<World::Mob>& enemies, const World::Mob& player);
  //void SendSensorResponse(const Bot bot);

private:
  Poco::Net::SocketStream& sstream;
  Messages::Header header;
  Messages::ActionRequest actionRequest;
  Messages::ActionResponse actionResponse;
  Messages::BotStatus botStatus;
  Messages::Enemy enemy;
  Messages::GameInfo gameInfo;
  Messages::Handshake handshake;
  Messages::Map map;
  Messages::SensorRequest sensorRequest;
  Messages::SensorResponse sensorResponse;
};

}
}

#endif
