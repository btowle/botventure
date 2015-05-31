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

  bool GetNextMessage();
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
  Messages::GameInfo gameInfo;
  Messages::Handshake handshake;
  Messages::SensorRequest sensorRequest;
  Messages::SensorResponse sensorResponse;
  ::google::protobuf::Message* currentMessage;
};

}
}

#endif
