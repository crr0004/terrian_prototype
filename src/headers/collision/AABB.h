#ifndef COLLSION_AABB
#define COLLSION_AABB 1
#include <glm/glm.hpp>
#include <float.h>
#define EPSILON FLT_EPSILON
namespace Collision{
	
	struct AABB{
		glm::vec3 min;
		glm::vec3 max;
	};
	// Test if segment specified by points p0 and p1 intersects AABB b
	 static int TestSegmentAABB(glm::vec3 p0, glm::vec3 p1, AABB b){
		 glm::vec3 c = (b.min + b.max) * 0.5f;
		 // Box center-point
		 glm::vec3 e = b.max - c;
		 // Box halflength extents
		 glm::vec3 m = (p0 + p1) * 0.5f;
		 // Segment midpoint
		 glm::vec3 d = p1 - m;
		 // Segment halflength vector
		 m = m - c;
		 // Translate box and segment to origin
		 // Try world coordinate axes as separating axes
		 float adx = glm::abs(d.x);
		 if (glm::abs(m.x) > e.x + adx) return 0;
		 float ady = glm::abs(d.y);
		 if (glm::abs(m.y) > e.y + ady) return 0;
		 float adz = glm::abs(d.z);
		 if (glm::abs(m.z) > e.z + adz) return 0;
		 // Add in an epsilon term to counteract arithmetic errors when segment is
		 // (near) parallel to a coordinate axis (see text for detail)
		 adx += EPSILON; ady += EPSILON; adz += EPSILON;
		 // Try cross products of segment direction vector with coordinate axes
		 if (glm::abs(m.y * d.z - m.z * d.y) > e.y * adz + e.z * ady) return 0;
		 if (glm::abs(m.z * d.x - m.x * d.z) > e.x * adz + e.z * adx) return 0;
		 if (glm::abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx) return 0;
		 // No separating axis found; segment must be overlapping AABB
		 return 1;
	 }
	 

}
#endif /* ifndef COLLSION_AABB */
