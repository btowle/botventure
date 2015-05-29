#include "messagereader.hpp"

namespace Botventure{
namespace Network{

  Messages::Header::MessageType MessageReader::GetNextMessage(){
    sstream >> headerSize;
    sstream.read(buffer.data(), headerSize);
    if(!header.ParseFromArray(buffer.data(), headerSize)){
      throw std::runtime_error("Could not parse header");
    }
    messageLength = header.message_length();
    messageType = header.message_type();
    sstream.read(buffer.data(), messageLength);
    bool parsed;
    switch(messageType){
      case Messages::Header::ACTIONREQUEST:
        parsed = actionRequest.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &actionRequest;
        break;
      case Messages::Header::ACTIONRESPONSE:
        parsed = actionResponse.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &actionResponse;
        break;
      case Messages::Header::BOTSTATUS:
        parsed = botStatus.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &botStatus;
        break;
      case Messages::Header::ENEMY:
        parsed = enemy.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &enemy;
        break;
      case Messages::Header::HANDSHAKE:
        parsed = handshake.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &handshake;
        break;
      case Messages::Header::MAP:
        parsed = map.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &map;
        break;
      case Messages::Header::SENSORREQUEST:
        parsed = sensorRequest.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &sensorRequest;
        break;
      case Messages::Header::SENSORRESPONSE:
        parsed = sensorResponse.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &sensorResponse;
        break;
      case Messages::Header::TURN:
        parsed = turn.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &turn;
        break;
      case Messages::Header::ERROR:
      default:
        parsed = header.ParseFromArray(buffer.data(), messageLength);
        currentMessage = &header;
        break;
    }
    if(!parsed){
      throw std::runtime_error("Could not parse mesesage.");
    }
    return messageType;
  }
  
  Messages::Header::MessageType MessageReader::CurrentMessageType() const{
    return messageType;
  }

}
}
