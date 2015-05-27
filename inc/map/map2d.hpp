#ifndef map_map2d_
#define map_map2d_

#include "messages/header.pb.h"
#include "messages/map.pb.h"
#include <vector>
#include "Poco/Net/SocketStream.h"

namespace Botventure{
namespace Map{

class Map2D{
public:
	Map2D(int width, int height) : width(width), height(height), nodes(width*height, Messages::Map::GROUND){}
	explicit Map2D(const Messages::Map& msg);
	~Map2D(){}
	
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	int Index(int x, int y);
	
	void FillMessage(Messages::Map& message);
	void FillMessage(Messages::Header& header, Messages::Map& message);
	bool SendMap(Poco::Net::SocketStream& sstream);
private:
	int width;
	int height;
	std::vector<Messages::Map::NodeType> nodes;
	
	Messages::Header header;
	Messages::Map mapMessage;
};

}
}

#endif