#ifndef COLLISION_PLANE
#define COLLISION_PLANE 1
#include <glm/glm.hpp>
namespace Collision{
	struct Plane{
		float d;
		glm::vec3 n;
	};
	static int PlaneLineColides(const glm::vec3 a, const glm::vec3 b, const Plane p, float &t, glm::vec3 &q){
		glm::vec3 ab = b - a;
		t = (p.d - glm::dot(p.n, a)) / glm::dot(p.n, ab);

		if(t >= 0.0f && t <= 1.0f){
			q = a + t * ab;
			return 1;
		}

		return 0;

	}

};
#endif /* ifndef COLLISION_POLYGON */
