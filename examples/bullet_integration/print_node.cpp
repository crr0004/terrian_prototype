#include "print_node.hpp"
#include <fmt/format.h>
PrintNode::PrintNode(){

}
int PrintNode::visit(INode* node){
	node->visit(this);
	fmt::print("Inside PrintNode INode\n");
	return 0;
}

int PrintNode::visit(PrintNode* node){
	fmt::print("Inside PrintNode print node\n");
	return 0;
}
