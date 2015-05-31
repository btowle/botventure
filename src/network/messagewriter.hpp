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
  void SendGameInfo();
  void SendHandshake(Messages::Handshake::Step step);
  void SendSensorRequest();
  void SendSensorResponse();

private:
  Poco::Net::SocketStream& sstream;
  Messages::Header header;
  Messages::ActionRequest actionRequest;
  Messages::ActionResponse actionResponse;
  Messages::GameInfo gameInfo;
  Messages::Handshake handshake;
  Messages::SensorRequest sensorRequest;
  Messages::SensorResponse sensorResponse;
};

}
}

#endif
