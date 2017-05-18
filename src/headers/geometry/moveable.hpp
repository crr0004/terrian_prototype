#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "node.hpp"
namespace Geometry {
	class Moveable : public Node{
		public:
			virtual void operation();
			virtual int visit(Moveable*);
			virtual int visit(INode* node){node->visit(this);}
	};
} // namespace Geometry
#endif
