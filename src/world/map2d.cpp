#include "map2d.hpp"
#include "mob.hpp"
#include "position.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include "Poco/File.h"

namespace Botventure{
namespace World{
	
	Map2D::Map2D(const Messages::Map& msg) : width(msg.width()), height(msg.height()), nodes(width*height, Messages::UNKNOWN){
		for(int i=0; i<msg.nodes_size(); ++i){
			nodes[i] = msg.nodes(i);
		}
	}

  void Map2D::Load(const std::string fileName){
    std::string fullFileName;
    if(Poco::File("../data/maps/" + fileName).exists()){
      fullFileName = "../data/maps/" + fileName;
    }else if(Poco::File("./data/maps/" + fileName).exists()){
      fullFileName = "./data/maps/" + fileName;
    }else{
      fullFileName = fileName;
    }
    std::string line;
    int maxLength = 0;
    std::vector<std::string> lines;
    std::ifstream mapFile(fullFileName);
    if(mapFile.is_open())
    {
      while(getline(mapFile, line)){
        if(line.length() > maxLength){
          maxLength = line.length();
        }
        lines.push_back(line);
      }
      width = maxLength;
      height = lines.size();
      nodes = std::vector<Terrain>(width*height, Messages::WALL);
      for(int y=0; y<height; ++y){
        //lines are reversed since text is opposite of internal storage.
        std::string s = lines[height - y - 1];
        for(int x=0; x<s.length(); ++x){
          if(s[x] == '&'){
            enemySpawns.push_back(Position(x,y));
          }
          if(s[x] == '@'){
            playerSpawn = Position(x,y);
          }
          GetNode(x,y) = CharToTerrain(s[x]);
        }
      }
    }else{
      throw std::runtime_error("could not open map file");
    }
  }

  std::string Map2D::ToString() const{
    std::stringstream ss;
    for(int y=height-1; y>=0; --y){
      for(int x=0; x<width; ++x){
        Terrain t = GetNode(x,y);
        ss << TerrainToChar(t);
      }
      if(y > 0){
        ss << std::endl;
      }
    }
    return ss.str();
  }

  std::string Map2D::ToString(const std::vector<Mob>& enemies, const Mob& player) const{
    std::stringstream ss;
    for(int y=height-1; y>=0; --y){
      for(int x=0; x<width; ++x){
        auto it = std::find_if(enemies.begin(), enemies.end(),
                              [x, y](const Mob& m)->bool{
                                return m.position == Position(x,y);
                              });
        if(player.position == Position(x,y)){
          ss << player.symbol;
        }else if(it != enemies.end()){
          if((*it).alive){
            ss << (*it).symbol;
          }else{
            ss << '.';
          }
        }else{
          Terrain t = GetNode(x,y);
          ss << TerrainToChar(t);
        }
      }
      if(y > 0){
        ss << std::endl;
      }
    }
    return ss.str();
  }

	Terrain& Map2D::GetNode(int index){
		return nodes[index];
	}

	const Terrain& Map2D::GetNode(int index) const{
		return nodes[index];
	}

  Terrain& Map2D::GetNode(Position p){
    return Map2D::GetNode(p.x, p.y);
  }

  const Terrain& Map2D::GetNode(Position p) const{
    return Map2D::GetNode(p.x, p.y);
  }

	Terrain& Map2D::GetNode(int x, int y){
		return GetNode(Index(x,y));
	}

	const Terrain& Map2D::GetNode(int x, int y) const{
		return GetNode(Index(x,y));
	}

	int Map2D::Index(int x, int y) const{
		return y*width + x;
	}

  Terrain Map2D::CharToTerrain(const char& c){
    static std::map<char, Messages::NodeType> map;
    if(map.empty()){
      map[' '] = Messages::GROUND;
      map['X'] = Messages::WALL;
      map['?'] = Messages::UNKNOWN;
      map['G'] = Messages::GOAL;
    }
    if(map.count(c)){
      return map[c];
    }
    return Messages::GROUND;
  }

  char Map2D::TerrainToChar(const Terrain& t){
    static std::map<Messages::NodeType, char> map;
    if(map.empty()){
      map[Messages::GROUND] = ' ';
      map[Messages::WALL] = 'X';
      map[Messages::UNKNOWN] = '?';
      map[Messages::GOAL] = 'G';
    }
    if(map.count(t)){
      return map[t];
    }
    return 'X';
  }

  bool Map2D::IsInBounds(Position p) const{
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < width;
  }
}
}
