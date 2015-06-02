#include "map2d.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

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
          GetNode(x,y) = CharToTerrain(s[x]);
        }
      }
      std::cout << "map" << width << "," << height << std::endl;
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
    switch(c){
      case ' ':
        return Messages::Map::GROUND;
        break;
      case 'X':
        return Messages::Map::WALL;
        break;
      case '?':
        return Messages::Map::UNKNOWN;
        break;
      default:
        return Messages::Map::WALL;
        break;
    }
  }

  char Map2D::TerrainToChar(const Terrain& t){
    switch(t){
      case Messages::Map::GROUND:
        return ' ';
        break;
      case Messages::Map::WALL:
        return 'X';
        break;
      case Messages::Map::UNKNOWN:
        return '?';
        break;
      default:
        return '?';
        break;
    }
  }
}
}
