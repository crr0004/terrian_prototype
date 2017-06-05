#ifndef COLLISION_COLLIDER_H
#define COLLISION_COLLIDER_H
#include "node.hpp"
#include "patterns/command.hpp"
#include "geometry/moveable.hpp"
namespace Collision {
	class AABBCollider;
	class SphereCollider;
	class Collider : public Node {
		public:
			virtual Geometry::Moveable& getMoveable() = 0;
			virtual bool visitCollide(Collider*) = 0;
			virtual bool visitCollide(AABBCollider*){return false;}
			virtual bool visitCollide(SphereCollider*){return false;}

			virtual void visitNotifyCollider(Collider*) = 0;
			virtual void visitNotifyCollider(AABBCollider*){}
			virtual void visitNotifyCollider(SphereCollider*){}
	};
} // namespace Collision
#endif
