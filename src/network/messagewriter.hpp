#ifndef network_messagewriter_
#define network_messagewriter_

#include "messages.hpp"
#include "../map/map2d.hpp"
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Network{

class MessageWriter
{
public:
  MessageWriter(Poco::Net::SocketStream& sstream) : sstream(sstream) {}
  ~MessageWriter() {}

  void SendMessage(const Messages::Header& msg) const;
  //void SendMap(const Map::Map2D& map);
  void SendActionRequest();
  void SendActionResponse();
  void SendGameInfo(int turnNumber);
  void SendHandshake(Messages::Handshake::Step step);
  void SendSensorRequest(Messages::BotStatus::SensorType sensor);
  void SendSensorResponse(const Map::Map2D& map);
  //void SendSensorResponse(const Bot bot);

private:
  Poco::Net::SocketStream& sstream;
  Messages::Header header;
  Messages::ActionRequest actionRequest;
  Messages::ActionResponse actionResponse;
  Messages::BotStatus botStatus;
  Messages::GameInfo gameInfo;
  Messages::Handshake handshake;
  Messages::Map map;
  Messages::SensorRequest sensorRequest;
  Messages::SensorResponse sensorResponse;
};

}
}

#endif
