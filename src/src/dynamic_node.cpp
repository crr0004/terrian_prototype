#include "dynamics/dynamic_node.hpp"
#include <fmt/format.h>

using namespace Dynamics;

DynamicNode::DynamicNode(){

}

int DynamicNode::visit(DynamicNode*){
	return 0;
}

int DynamicNode::visit(INode* node){
	node->visit(this);
	return 0;
}

void DynamicNode::step(double t, double dt){

}
