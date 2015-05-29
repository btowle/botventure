#include "map/map2d.hpp"
#include <iostream>
namespace Botventure{
namespace Map{
	
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
	
	void Map2D::FillMessage(Messages::Map& message) const{
		message.set_width(width);
		message.set_height(height);
		message.clear_nodes();
		for(Terrain n : nodes){
			message.add_nodes(n);
		}
	}
	
	void Map2D::FillMessage(Messages::Header& header, Messages::Map& message) const{
		FillMessage(message);
		
		header.set_message_type(Messages::Header::MAP);
		header.set_message_length(message.ByteSize());
	}
	
	bool Map2D::SendMap(Poco::Net::SocketStream& sstream) const{
		FillMessage(header, mapMessage);
		sstream << header.ByteSize();
		if(!header.SerializeToOstream(&sstream)){
			return false;
		}
		if(!mapMessage.SerializeToOstream(&sstream)){
			return false;	
		}
		return true;
	}
}
}
