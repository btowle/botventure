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

  void MessageWriter::SendActionRequest(Messages::ActionType type, Messages::Direction direction){
    header.set_message_type(Messages::ACTIONREQUEST);
    actionRequest.set_action_type(type);
    actionRequest.set_direction(direction);
    header.mutable_action_request()->CopyFrom(actionRequest);
    SendMessage(header);
  }

  void MessageWriter::SendActionResponse(bool result){
    header.set_message_type(Messages::ACTIONRESPONSE);
    actionResponse.set_result(result);
    header.mutable_action_response()->CopyFrom(actionResponse);
    SendMessage(header);
  }

  void MessageWriter::SendGameInfo(int turnNumber, Messages::GameState gameState){
    header.set_message_type(Messages::GAMEINFO);
    gameInfo.set_turn_number(turnNumber);
    gameInfo.set_game_state(gameState);
    header.mutable_game_info()->CopyFrom(gameInfo);
    SendMessage(header);
  }

  void MessageWriter::SendHandshake(Messages::Step step){
    header.set_message_type(Messages::HANDSHAKE);
    handshake.set_step(step);
    header.mutable_handshake()->CopyFrom(handshake);
    SendMessage(header);
  }

  void MessageWriter::SendSensorRequest(Messages::SensorType sensor){
    header.set_message_type(Messages::SENSORREQUEST);
    sensorRequest.set_sensor_type(sensor);
    header.mutable_sensor_request()->CopyFrom(sensorRequest);
    SendMessage(header);
  }

  void MessageWriter::SendSensorResponse(const World::Map2D& m){
    header.set_message_type(Messages::SENSORRESPONSE);
    map.set_width(m.GetWidth());
    map.set_height(m.GetHeight());
    map.clear_nodes();
    for(World::Terrain n : m.GetNodes()){
      map.add_nodes(n);
    }
    sensorResponse.mutable_map()->CopyFrom(map);
    sensorResponse.set_sensor_type(Messages::GPS);
    header.mutable_sensor_response()->CopyFrom(sensorResponse);
    SendMessage(header);
  }

  void MessageWriter::SendSensorResponse(const World::Map2D& m, const std::vector<World::Mob>& enemies, const World::Mob& player){
    header.set_message_type(Messages::SENSORRESPONSE);
    map.set_width(m.GetWidth());
    map.set_height(m.GetHeight());
    map.clear_nodes();
    for(World::Terrain n : m.GetNodes()){
      map.add_nodes(n);
    }
    sensorResponse.mutable_map()->CopyFrom(map);

    sensorResponse.clear_enemies();
    for(World::Mob mob : enemies){
      enemy.set_health(mob.health);
      enemy.set_x(mob.position.x);
      enemy.set_y(mob.position.y);
      sensorResponse.add_enemies()->CopyFrom(enemy);
    }

    botStatus.set_health(player.health);
    botStatus.set_x(player.position.x);
    botStatus.set_y(player.position.y);
    sensorResponse.mutable_bot_status()->CopyFrom(botStatus);

    sensorResponse.set_sensor_type(Messages::GPS);
    header.mutable_sensor_response()->CopyFrom(sensorResponse);
    SendMessage(header);
  }

}
}
