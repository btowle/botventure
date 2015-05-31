#include "messagewriter.hpp"

namespace Botventure{
namespace Network{

  void MessageWriter::SendMessage(const Messages::Header& msg) const{
    sstream << header.ByteSize();
    if(!header.SerializeToOstream(&sstream)){
      throw std::runtime_error("Could not serialize header");
    }
    sstream << std::flush;
  }

/*
  void MessageWriter::SendMap(const Map::Map2D& map){
    header.set_message_type(Messages::Header::MAP);
    Messages::Map mapMessage;
    mapMessage.set_width(map.GetWidth());
    mapMessage.set_height(map.GetHeight());
    for(Map::Terrain n : map.GetNodes()){
      mapMessage.add_nodes(n);
    }
    header.mutable_map()->CopyFrom(mapMessage);

    SendMessage(header);
  }
*/
  void MessageWriter::SendActionRequest(){
    header.set_message_type(Messages::Header::ACTIONREQUEST);
    //set things on actionRequest
    header.mutable_action_request()->CopyFrom(actionRequest);
    SendMessage(header);
  }

  void MessageWriter::SendActionResponse(){
    header.set_message_type(Messages::Header::ACTIONRESPONSE);
    //set things on actionResponse
    header.mutable_action_response()->CopyFrom(actionResponse);
    SendMessage(header);
  }

  void MessageWriter::SendGameInfo(){
    header.set_message_type(Messages::Header::GAMEINFO);
    //set things on gameInfo
    header.mutable_game_info()->CopyFrom(gameInfo);
    SendMessage(header);
  }

  void MessageWriter::SendHandshake(Messages::Handshake::Step step){
    header.set_message_type(Messages::Header::HANDSHAKE);
    handshake.set_step(step);
    header.mutable_handshake()->CopyFrom(handshake);
    SendMessage(header);
  }

  void MessageWriter::SendSensorRequest(){
    header.set_message_type(Messages::Header::SENSORREQUEST);
    //set things on sensorRequest
    header.mutable_sensor_request()->CopyFrom(sensorRequest);
    SendMessage(header);
  }

  void MessageWriter::SendSensorResponse(){
    header.set_message_type(Messages::Header::SENSORRESPONSE);
    //set things on sensorResponse
    header.mutable_sensor_response()->CopyFrom(sensorResponse);
    SendMessage(header);
  }

}
}
