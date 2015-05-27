#include "map/map2d.hpp"
#include <iostream>
namespace Botventure{
namespace Map{
	
	Map2D::Map2D(const Messages::Map& msg) : width(msg.width()), height(msg.height()), nodes(width*height, Messages::Map::UNKNOWN){
		for(int i=0; i<msg.nodes_size(); ++i){
			nodes[i] = msg.nodes(i);
		}
	}
	
	int Map2D::Index(int x, int y){
		return y*width + x;
	}
	
	void Map2D::FillMessage(Messages::Map& message){
		message.set_width(width);
		message.set_height(height);
		message.clear_nodes();
		for(Messages::Map::NodeType n : nodes){
			message.add_nodes(n);
		}
	}
	
	void Map2D::FillMessage(Messages::Header& header, Messages::Map& message){
		FillMessage(message);
		
		header.set_messagetype(Messages::Header::MAP);
		header.set_messagelength(message.ByteSize());
	}
	
	bool Map2D::SendMap(Poco::Net::SocketStream& sstream){
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