#ifndef COLLISION_SIMPLEWORLD_H
#define COLLISION_SIMPLEWORLD_H
#include "node.hpp"
#include "collision/collider.hpp"
namespace Collision {
	class SimpleWorld : public Node{
		public:
			virtual void operation();
			virtual void add(INode*);
			virtual void add(Collider*);
	};
} // namespace Collision
#endif
