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
      case Messages::Header::ACTIONREQUEST:
        actionRequest = header.action_request();
        currentMessage = &actionRequest;
        break;
      case Messages::Header::ACTIONRESPONSE:
        actionResponse = header.action_response();
        currentMessage = &actionResponse;
        break;
      case Messages::Header::GAMEINFO:
        gameInfo = header.game_info();
        currentMessage = &gameInfo;
        break;
      case Messages::Header::HANDSHAKE:
        handshake = header.handshake();
        currentMessage = &handshake;
        break;
      case Messages::Header::SENSORREQUEST:
        sensorRequest = header.sensor_request();
        currentMessage = &sensorRequest;
        break;
      case Messages::Header::SENSORRESPONSE:
        sensorResponse = header.sensor_response();
        currentMessage = &sensorResponse;
        break;
      case Messages::Header::ERROR:
      default:
        currentMessage = &header;
        break;
    }
    return true;
  }
  
  Messages::Header::MessageType MessageReader::CurrentMessageType() const{
    return messageType;
  }

}
}
