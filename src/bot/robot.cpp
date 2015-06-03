#include "robot.hpp"

namespace Botventure{
namespace Bot{

bool Robot::Connect(){
  mWriter.SendHandshake(Messages::Handshake::SYN);
  if(!mReader.GetNextMessage() || 
  mReader.CurrentMessageType() != Messages::Header::HANDSHAKE || 
  mReader.CurrentMessage<Messages::Handshake>().step() != Messages::Handshake::ACK)
  {  
    connected = false;
    return connected;
  }  
  mWriter.SendHandshake(Messages::Handshake::NEWGAME);
  return GetNextTurn();
}

bool Robot::IsPlaying(){
  return playing;
}
bool Robot::IsWinner(){
  return winner;
}

int Robot::GetTurn(){
  return currentTurn;
}

World::Map2D Robot::GetMap(){
  if(mapTurn != currentTurn){
    RequestMap();
  }
  return map;
}

std::vector<World::Mob> Robot::GetEnemies(){
  if(enemiesTurn != currentTurn){
    RequestMap();
  }
  return enemies;
}

World::Mob Robot::GetPlayer(){
  if(playerTurn != currentTurn){
    RequestMap();
  }
  return player;
}

bool Robot::Move(Direction direction){
  if(!connected){ return false; }
  mWriter.SendActionRequest(Messages::ActionRequest::MOVE, direction);
  if(!mReader.GetNextMessage() ||
  mReader.CurrentMessageType() != Messages::Header::ACTIONRESPONSE){
    connected = false;
    return false;
  }
  if(mReader.CurrentMessage<Messages::ActionResponse>().result() == false){
    GetNextTurn();
    return false;
  }
  GetNextTurn();
  return true;
}

bool Robot::RequestMap(){
  if(!connected){ return false; }
  mWriter.SendSensorRequest(Messages::BotStatus::GPS);
  if(!mReader.GetNextMessage() || 
  mReader.CurrentMessageType() != Messages::Header::SENSORRESPONSE || 
  mReader.CurrentMessage<Messages::SensorResponse>().sensor_type() != Messages::BotStatus::GPS){
    connected = false;
    return false;
  }  
  Messages::SensorResponse msg = mReader.CurrentMessage<Messages::SensorResponse>();
  Messages::Map mapMessage = msg.map();

  mapTurn = currentTurn;
  map = World::Map2D(mapMessage);

  enemiesTurn = currentTurn;
  enemies.clear();
  for(int i=0; i<msg.enemies_size(); ++i){
    Messages::Enemy e = msg.enemies(i);
    enemies.push_back(World::Mob(World::Position(e.x(), e.y()), e.health()));
  }

  playerTurn = currentTurn;
  Messages::BotStatus b = msg.bot_status();
  player = World::Mob(World::Position(b.x(), b.y()), b.health());
}

bool Robot::GetNextTurn(){
  if(mReader.GetNextMessage() &&
     mReader.CurrentMessageType() == Messages::Header::GAMEINFO){
    Messages::GameInfo msg = mReader.CurrentMessage<Messages::GameInfo>();
    currentTurn = msg.turn_number();
    Messages::GameState state = msg.game_state();
    if(state == Messages::SUCCESS){
      winner = true;
      playing = false;
    }
    if(state == Messages::FAILURE){
      winner = false;
      playing = false;
    }
    connected = true;
    return true;
  }
  connected = false;
  return false;
}

}
}
