#ifndef BULLET_CONTACTMANIFOLD_NODE_H
#define BULLET_CONTACTMANIFOLD_NODE_H
#include "bullet_node.hpp"
class BulletContactManifoldNode : public BulletNode{
	public:
		BulletContactManifoldNode(btPersistentManifold*);
		btPersistentManifold* getManifold();
		virtual int visit(INode*);
		virtual int visit(BulletNode*);
	private:
		btPersistentManifold* lastManifold;
};
#endif
