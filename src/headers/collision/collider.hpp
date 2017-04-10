#ifndef COLLISION_COLLIDER_H
#define COLLISION_COLLIDER_H
#include "collision/node.hpp"
namespace Collision {
	class AABBCollider;
	class SphereCollider;
	class Collider : public Node {
		public:
			virtual bool visitCollide(Collider*) = 0;
			virtual bool visitCollide(AABBCollider*){return false;}
			virtual bool visitCollide(SphereCollider*){return false;}
	};
} // namespace Collision
#endif
