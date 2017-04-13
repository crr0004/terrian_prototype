#ifndef COLLSION_SPHERE_COLLIDER
#define COLLSION_SPHERE_COLLIDER
#include "collision/collider.hpp"
#include <glm/glm.hpp>
namespace Collision {
	class SphereCollider : public Collider {
		public:
			SphereCollider(const glm::vec3&, const float);
			virtual bool visitCollide(Collider*);
			virtual bool visitCollide(AABBCollider*);
			virtual bool visitCollide(SphereCollider*);
			virtual void visitNotifyCollider(Collider*){}
			virtual void add(INode*){}
			virtual int insert(INode*){return -1;}
			virtual void remove(int){}
			virtual int getChildCount(){return 0;}
			virtual INode* getChild(int){return 0;}
		protected:
			glm::vec3 center;
			float radius;

	};
} // namespace Collision
#endif
