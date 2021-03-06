#ifndef world_map2d_
#define world_map2d_

#ifdef RAKE_COMPILATION
#include "messages.hpp"
#else
#include "network/messages.hpp"
#endif //RAKE_COMPILATION
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

  void Load(const std::string campaignName, const std::string fileName);
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
  int IndexOf(Position p) const;
  Position PositionOf(int index) const;

  bool IsInBounds(Position p) const;

  std::vector<Position> enemySpawns;
  Position playerSpawn;

private:
	int width;
	int height;
	std::vector<Terrain> nodes;
};

}
}

#endif
