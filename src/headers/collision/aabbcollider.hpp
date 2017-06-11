#ifndef COLLSION_AABB_COLLIDER
#define COLLSION_AABB_COLLIDER
#include "collision/collider.hpp"
#include "geometry/moveable.hpp"
#include <glm/glm.hpp>
namespace Collision {
	class AABBCollider : public Collider {
		public:
			AABBCollider(const glm::vec3&, const glm::vec3&);
			virtual bool visitCollide(Collider*);
			virtual bool visitCollide(AABBCollider*);
			virtual bool visitCollide(SphereCollider*);
			virtual void notifyCollider(Collider*);
			virtual unsigned long int getCategoryID(){return 0;}
			virtual bool collides(const AABBCollider&);
			virtual void add(INode*){}
			virtual int insert(INode*){return -1;}
			virtual void remove(int){}
			virtual int getChildCount(){return 0;}
			virtual INode* getChild(int){return 0;}
			virtual Geometry::Moveable& getMoveable();
			const glm::vec3& getMin(){return min;}
			const glm::vec3& getMax(){return max;}
			glm::vec3 getTransformedMin();
			glm::vec3 getTransformedMax();
		protected:
			glm::vec3 min;
			glm::vec3 max;
			Geometry::Moveable moveable;

	};
} // namespace Collision
#endif
