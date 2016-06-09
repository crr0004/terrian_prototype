#include <catch.hpp>
#include "matrixstacksingleton.h"
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>

TEST_CASE("Polygon initialization"){
	SECTION("Vertices should only store reference"){
		REQUIRE(false);
	}
	SECTION("Indices should only store reference"){
		REQUIRE(false);
	}
	SECTION("indicesSize should be the amount of triangles to draw"){
		REQUIRE(false);
	} 
	SECTION("Model matrix should start as identity matrix"){
		REQUIRE(false);
	}

}

TEST_CASE("Polygon use"){
	SECTION("Model matrix should reset after drawing"){
		REQUIRE(false);
	}
	SECTION("Translating should chang the model matrix"){
		REQUIRE(false);
	}
	SECTION("buildStatic should allocate opengl drawing states"){
		REQUIRE(false);
	}
	SECTION("draw should bind and un-bind opengl buffers"){
		REQUIRE(false);
	}
}
