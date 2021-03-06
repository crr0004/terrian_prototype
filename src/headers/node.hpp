#ifndef COLLISION_NODE_H
#define COLLISION_NODE_H
#include "INode.hpp"
#include "patterns/command.hpp"
#include <vector>
class Node : public INode{
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
		virtual int visit(Node*);
		virtual ~Node();
		Node();
		Node(int);
	protected:
		std::vector<INode*> children;
		INode* parent;

};	
#endif
