#ifndef COLLISION_SIMPLEWORLD_H
#define COLLISION_SIMPLEWORLD_H
#include "collision/collider.hpp"
namespace Collision {
	class SimpleWorld : public Collider{
		public:
			virtual void operation();
			virtual void add(INode*);
			virtual void add(Collider*);
			virtual void notifyCollider(Collider*){}
			virtual Geometry::Moveable& getMoveable(){return moveable;}
			virtual bool visitCollide(Collider* collider){return collider->visit(this);} 
		private: 
			Geometry::Moveable moveable;
	};
} // namespace Collision
#endif
