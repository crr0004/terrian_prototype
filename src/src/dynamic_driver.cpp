#include "dynamics/dynamic_driver.hpp"
#include <fmt/format.h>

using namespace Dynamics;
DynamicDriver::DynamicDriver(){
	t = -1;
	dt = -2;

}

void DynamicDriver::operation(){
	for(int i = 0; i < children.size(); i++){
		children.at(i)->operation();
		children.at(i)->visit((INode*)this);
	}
}

void DynamicDriver::add(INode* node){
	children.push_back(node);
	node->setParent(this);
}

void DynamicDriver::add(DynamicNode* node){
	children.push_back(node);
	node->setParent(this);
}

int DynamicDriver::visit(DynamicNode* node){
	node->step(this->t, this->dt);

	return 0;
}

int DynamicDriver::visit(INode*){

	return 0;

}
