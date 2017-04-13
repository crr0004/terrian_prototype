#ifndef COLLISION_NODE_H
#define COLLISION_NODE_H
#include "collision/INode.hpp"
#include <vector>
namespace Collision {
	class Node : public INode{
		public:
			virtual void operation(){}
			virtual void add(INode*);
			virtual int insert(INode*);
			virtual void remove(int);
			virtual int getChildCount();
			virtual INode* getChild(int);
			virtual void setParent(INode*);
			virtual INode* getParent();
			virtual ~Node();
			Node();
			Node(int);
		protected:
			std::vector<INode*> children;
			INode* parent;

	};	
} // namespace Collision
#endif
