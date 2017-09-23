#include "bullet_contactmanifold_node.hpp"
#include <fmt/format.h>

BulletContactManifoldNode::BulletContactManifoldNode(btPersistentManifold* manifold){
	this->lastManifold = manifold;
}
btPersistentManifold* BulletContactManifoldNode::getManifold(){
	return this->lastManifold;
}
int BulletContactManifoldNode::visit(INode* node){
	node->visit(this);
	return 0;
}
int BulletContactManifoldNode::visit(BulletNode* node){
	node->visit(this);
	return 0;
}
