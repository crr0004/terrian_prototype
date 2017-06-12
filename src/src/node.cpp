#include "node.hpp"

Command* command = 0;
Node::Node(){

}

Node::Node(int initialSize){
	children.reserve(initialSize);
}

Node::~Node(){
	children.clear();
}

void Node::add(INode* node){
	children.push_back(node);
	node->setParent(this);
}
int Node::insert(INode* node){
	this->add(node);
	return children.size()-1;
}

void Node::remove(int i){
	children.erase(children.begin() + i);

}

void Node::setParent(INode* node){
	parent = node;

}

INode* Node::getParent(){
	return parent;

}

int Node::getChildCount(){

	return children.size();
}

INode* Node::getChild(int i){

	return children.at(i);

}

void Node::operation(){
	for(int i = 0; i < children.size(); i++){
		children.at(i)->operation();
	}
}

int Node::visit(INode* node){
	return node->visit(this);
}
int Node::visit(Node* node){
	node->operation();
	return 0;
}
