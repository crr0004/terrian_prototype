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
			virtual void visitNotifyCollider(Collider*);
			virtual void add(INode*){}
			virtual int insert(INode*){return -1;}
			virtual void remove(int){}
			virtual int getChildCount(){return 0;}
			virtual INode* getChild(int){return 0;}
			glm::vec3 getCenter(){	return glm::vec3(moveable.getCulumativeMatrix() * glm::vec4(center, 1.0f)); }
			virtual Geometry::Moveable& getMoveable();
		protected:
			glm::vec3 center;
			float radius;
			Geometry::Moveable moveable;

	};
} // namespace Collision
#endif
