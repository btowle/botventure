#include "map2d.hpp"
#include <iostream>
namespace Botventure{
namespace World{
	
	Map2D::Map2D(const Messages::Map& msg) : width(msg.width()), height(msg.height()), nodes(width*height, Messages::Map::UNKNOWN){
		for(int i=0; i<msg.nodes_size(); ++i){
			nodes[i] = msg.nodes(i);
		}
	}

	Terrain& Map2D::GetNode(int index){
		return nodes[index];
	}

	const Terrain& Map2D::GetNode(int index) const{
		return nodes[index];
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
}
}
