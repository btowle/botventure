#include "map2d.hpp"
#include "mob.hpp"
#include "position.hpp"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

namespace Botventure{
namespace World{
	
	Map2D::Map2D(const Messages::Map& msg) : width(msg.width()), height(msg.height()), nodes(width*height, Messages::Map::UNKNOWN){
		for(int i=0; i<msg.nodes_size(); ++i){
			nodes[i] = msg.nodes(i);
		}
	}

  void Map2D::Load(const std::string fileName){
    std::string line;
    int maxLength = 0;
    std::vector<std::string> lines;
    std::ifstream mapFile(fileName);
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
      nodes = std::vector<Terrain>(width*height, Messages::Map::WALL);
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
        if(it != enemies.end()){
          ss << '&';
        }else if(player.position == Position(x,y)){
          ss << '@';
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
    static std::map<char, Messages::Map::NodeType> map;
    if(map.empty()){
      map[' '] = Messages::Map::GROUND;
      map['@'] = Messages::Map::GROUND;
      map['&'] = Messages::Map::GROUND;
      map['X'] = Messages::Map::WALL;
      map['?'] = Messages::Map::UNKNOWN;
    }
    if(map.count(c)){
      return map[c];
    }
    return Messages::Map::WALL;
  }

  char Map2D::TerrainToChar(const Terrain& t){
    static std::map<Messages::Map::NodeType, char> map;
    if(map.empty()){
      map[Messages::Map::GROUND] = ' ';
      map[Messages::Map::WALL] = 'X';
      map[Messages::Map::UNKNOWN] = '?';
    }
    if(map.count(t)){
      return map[t];
    }
    return 'X';
  }

  bool Map2D::InBounds(Position p) const{
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < width;
  }
}
}
