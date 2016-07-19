#include "collision/plane.h"
#include <catch.hpp>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <glm/gtx/string_cast.hpp>

using namespace Collision;

TEST_CASE("Plane collisions"){
	SECTION("Plane and line segment"){
		Plane p;
		p.d = 10.0f;
		p.n = glm::vec3(20.0f, 30.0f, 0.0f);
		glm::vec3 a = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 b = glm::vec3(40.0f, 60.0f, 0.0f);

		float t;
		glm::vec3 q;

		REQUIRE(PlaneLineColides(a, b, p, t, q) == 1);
		printf("t: %f, q: %s\n", t, glm::to_string(q).c_str());
	}

}
