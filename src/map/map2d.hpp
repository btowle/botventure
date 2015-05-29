#ifndef map_map2d_
#define map_map2d_

#include "../network/messages.hpp"
#include <vector>
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Map{

typedef Messages::Map::NodeType Terrain;

class Map2D{
public:
	Map2D(int width, int height) : width(width), height(height), nodes(width*height, Messages::Map::GROUND){}
	explicit Map2D(const Messages::Map& msg);
	~Map2D(){}
	
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	
	Terrain& GetNode(int index);
	const Terrain& GetNode(int index) const;
	Terrain& GetNode(int x, int y);
	const Terrain& GetNode(int x, int y) const;
	int Index(int x, int y) const;

	void FillMessage(Messages::Map& message) const;
	void FillMessage(Messages::Header& header, Messages::Map& message) const;
	bool SendMap(Poco::Net::SocketStream& sstream) const;
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
