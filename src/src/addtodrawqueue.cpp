#include "addtodrawqueue.hpp"
#include <fmt/format.h>

std::vector<IPolygon*>* AddToDrawQueueCommand::queue = 0;
IPolygon* drawHost = 0;

AddToDrawQueueCommand::AddToDrawQueueCommand(IPolygon* drawHost){
	this->drawHost = drawHost;
}

AddToDrawQueueCommand::~AddToDrawQueueCommand(){
	drawHost = 0;
}

void AddToDrawQueueCommand::SetQueue(std::vector<IPolygon*>* queue){
	AddToDrawQueueCommand::queue = queue;
}

void AddToDrawQueueCommand::execute(){
	if(queue != 0){
		queue->push_back(drawHost);
	}else{
		fmt::fprintf(stderr,"Error in AddToDrawQueueCommand, queue not set\n");
	}

}
