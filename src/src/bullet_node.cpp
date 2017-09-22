#include "bullet_node.hpp"


void BulletNode::operation(){

}
void BulletNode::add(INode*){

}
int BulletNode::insert(INode*){
	return -1;

}
void BulletNode::remove(int){

}
int BulletNode::getChildCount(){
	return 0;

}
INode* BulletNode::getChild(int){
	return nullptr;
}
void BulletNode::setParent(INode*){

}
INode* BulletNode::getParent(){
	return nullptr;
}
int BulletNode::visit(INode* node){
	node->visit(this);
	return 0;
}
