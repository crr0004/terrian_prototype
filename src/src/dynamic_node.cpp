#include "dynamics/dynamic_node.hpp"
#include <fmt/format.h>

using namespace Dynamics;

DynamicNode::DynamicNode(){

}

int DynamicNode::visit(DynamicNode*){

}

int DynamicNode::visit(INode* node){
	node->visit(this);
}

void DynamicNode::step(double t, double dt){

}
