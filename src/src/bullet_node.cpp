#include "bullet_node.hpp"
#include "bullet_contactmanifold_node.hpp"
#include <fmt/format.h>


/* -------------------------------*/
/** 
 * @brief BulletNode constuctor mainly used for debugging. No guarantee it
 * will remain
 * 
 * @Param ID set to whatever is needed, initially used for debugging.
 */
/* ---------------------------------*/
BulletNode::BulletNode(int ID){

	this->ID = ID;
}

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

int BulletNode::visit(BulletNode* node){
	fmt::printf("Inside BulletNode bulletnode ID: %d\n", this->ID);
	return 0;
}
int BulletNode::visit(BulletContactManifoldNode* node){
	fmt::printf("Inside BulletNode with contact manifold\n");
	return 0;
}
