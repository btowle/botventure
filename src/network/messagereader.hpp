#ifndef network_messagereader_
#define network_messagereader_

#include "messages.hpp"
#include <memory>
#include <vector>
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Network{

class MessageReader
{
public:
  MessageReader(Poco::Net::SocketStream& sstream) : sstream(sstream), buffer(256) {}
  ~MessageReader() {}

  Messages::Header::MessageType GetNextMessage();
  Messages::Header::MessageType CurrentMessageType() const;
  template <class T>
  const T& CurrentMessage() const{
    return dynamic_cast<T&>(*currentMessage);
  }
private:
  Poco::Net::SocketStream& sstream;

  Messages::Header header;
  int headerSize;
  int messageLength;
  Messages::Header::MessageType messageType;
  std::vector<char> buffer;

  Messages::ActionRequest actionRequest;
  Messages::ActionResponse actionResponse;
  Messages::BotStatus botStatus;
  Messages::Enemy enemy;
  Messages::Handshake handshake;
  Messages::Map map;
  Messages::SensorRequest sensorRequest;
  Messages::SensorResponse sensorResponse;
  Messages::Turn turn;
  ::google::protobuf::Message* currentMessage;
};

}
}

#endif
