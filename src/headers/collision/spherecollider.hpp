#ifndef COLLSION_SPHERE_COLLIDER
#define COLLSION_SPHERE_COLLIDER
#include "collision/collider.hpp"
#include "geometry/moveable.hpp"
#include <glm/glm.hpp>
namespace Collision {
	class SphereCollider : public Collider {
		public:
			SphereCollider(const glm::vec3&, const float);
			virtual bool visitCollide(Collider*);
			virtual bool visitCollide(AABBCollider*);
			virtual bool visitCollide(SphereCollider*);
			virtual void notifyCollider(Collider*);
			virtual unsigned long int getCategoryID(){return 0;}
			virtual void add(INode*){}
			virtual int insert(INode*){return -1;}
			virtual void remove(int){}
			virtual int getChildCount(){return 0;}
			virtual INode* getChild(int){return 0;}
			virtual glm::vec3 getTransformedCenter();
			virtual Geometry::Moveable& getMoveable();
			virtual float getRadius(){return radius;}
		protected:
			glm::vec3 center;
			float radius;
			Geometry::Moveable moveable;

	};
} // namespace Collision
#endif
