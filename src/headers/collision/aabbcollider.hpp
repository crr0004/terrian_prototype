#ifndef COLLSION_AABB_COLLIDER
#define COLLSION_AABB_COLLIDER
#include "collision/collider.hpp"
#include <glm/glm.hpp>
namespace Collision {
	class AABBCollider : public Collider {
		public:
			AABBCollider(const glm::vec3&, const glm::vec3&);
			virtual bool visitCollide(Collider*);
			virtual bool visitCollide(AABBCollider*);
			virtual bool visitCollide(SphereCollider*);
			virtual void visitNotifyCollider(Collider*);
			virtual void visitNotifyCollider(AABBCollider*){}
			virtual void visitNotifyCollider(SphereCollider*){}
			virtual bool collides(const AABBCollider&);
			virtual void add(INode*){}
			virtual int insert(INode*){return -1;}
			virtual void remove(int){}
			virtual int getChildCount(){return 0;}
			virtual INode* getChild(int){return 0;}
			const glm::vec3& getMin(){return min;}
			const glm::vec3& getMax(){return max;}
		protected:
			glm::vec3 min;
			glm::vec3 max;

	};
} // namespace Collision
#endif
