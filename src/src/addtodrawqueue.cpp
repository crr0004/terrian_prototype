#include "addtodrawqueue.hpp"
#include <fmt/format.h>

std::vector<Geometry::Polygon*>* AddToDrawQueueCommand::queue = 0;
Geometry::Polygon* drawHost = 0;

AddToDrawQueueCommand::AddToDrawQueueCommand(Geometry::Polygon* drawHost){
	this->drawHost = drawHost;
}

AddToDrawQueueCommand::~AddToDrawQueueCommand(){
	drawHost = 0;
}

void AddToDrawQueueCommand::SetQueue(std::vector<Geometry::Polygon*>* queue){
	AddToDrawQueueCommand::queue = queue;
}

void AddToDrawQueueCommand::execute(){
	if(queue != 0){
		queue->push_back(drawHost);
	}else{
		fmt::print(stderr,"Error in AddToDrawQueueCommand, queue not set\n");
	}

}
