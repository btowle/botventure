#include "messagereader.hpp"

namespace Botventure{
namespace Network{

  bool MessageReader::GetNextMessage(){
    sstream >> headerSize;
    if(sstream.eof()){
      return false;
    }
    while(headerSize > buffer.capacity()){
      buffer.resize(buffer.capacity() * 2);
    }
    sstream.read(buffer.data(), headerSize);

    if(!header.ParseFromArray(buffer.data(), headerSize)){
      throw std::runtime_error("Could not parse header");
    }
    messageType = header.message_type();

    switch(messageType){
      case Messages::ACTIONREQUEST:
        actionRequest = header.action_request();
        currentMessage = &actionRequest;
        break;
      case Messages::ACTIONRESPONSE:
        actionResponse = header.action_response();
        currentMessage = &actionResponse;
        break;
      case Messages::GAMEINFO:
        gameInfo = header.game_info();
        currentMessage = &gameInfo;
        break;
      case Messages::HANDSHAKE:
        handshake = header.handshake();
        currentMessage = &handshake;
        break;
      case Messages::SENSORREQUEST:
        sensorRequest = header.sensor_request();
        currentMessage = &sensorRequest;
        break;
      case Messages::SENSORRESPONSE:
        sensorResponse = header.sensor_response();
        currentMessage = &sensorResponse;
        break;
      case Messages::MESSAGEERROR:
      default:
        currentMessage = &header;
        break;
    }
    return true;
  }
  
  Messages::MessageType MessageReader::CurrentMessageType() const{
    return messageType;
  }

}
}
