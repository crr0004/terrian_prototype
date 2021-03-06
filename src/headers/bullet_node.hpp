#ifndef BULLET_NODE_H
#define BULLET_NODE_H
#include "INode.hpp"
#include <btBulletDynamicsCommon.h>
class BulletContactManifoldNode;
class BulletNode : public INode{
	public:
		virtual void operation();
		virtual void add(INode*);
		virtual int insert(INode*);
		virtual void remove(int);
		virtual int getChildCount();
		virtual INode* getChild(int);
		virtual void setParent(INode*);
		virtual INode* getParent();
		virtual int visit(INode*);
		virtual int visit(BulletNode*);
		virtual int visit(BulletContactManifoldNode*);
		BulletNode(int);
		BulletNode(){}
	private:
		int ID;
};
#endif
