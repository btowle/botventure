#ifndef world_map2d_
#define world_map2d_

#include "../network/messages.hpp"
#include "mob.hpp"
#include "position.hpp"
#include <string>
#include <utility>
#include <vector>
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace World{

typedef Messages::NodeType Terrain;

class Map2D{
public:
	Map2D(int width=1, int height=1) : width(width), height(height), nodes(width*height, Messages::GROUND){}
	explicit Map2D(const Messages::Map& msg);
	~Map2D(){}

  void Load(std::string const fileName);
  std::string ToString() const;
  std::string ToString(const std::vector<Mob>& enemies, const Mob& player) const;

  static Terrain CharToTerrain(const char& c);
  static char TerrainToChar(const Terrain& t);
	
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
  const std::vector<Terrain>& GetNodes() const { return nodes; }
	
	Terrain& GetNode(int index);
	const Terrain& GetNode(int index) const;

  Terrain& GetNode(Position p);
  const Terrain& GetNode(Position p) const;

	Terrain& GetNode(int x, int y);
	const Terrain& GetNode(int x, int y) const;

  int Index(int x, int y) const;

  bool InBounds(Position p) const;

  std::vector<Position> enemySpawns;
  Position playerSpawn;

private:
	int width;
	int height;
	std::vector<Terrain> nodes;
	
	mutable Messages::Header header;
	mutable Messages::Map mapMessage;
};

}
}

#endif
