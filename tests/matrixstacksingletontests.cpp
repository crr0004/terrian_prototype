#include <catch.hpp>
#include "matrixstacksingleton.hpp"
#include <glm/glm.hpp>
#include <stdio.h>
#include <iostream>

TEST_CASE("Matrix stack pushing and popping"){
	MatrixStackSingleton* instance = MatrixStackSingleton::instance();
	SECTION("getting instance shouldn't be null"){
		REQUIRE(instance != 0);
	}


	SECTION("matrix should become identity matrix on push"){
		using namespace glm;
		//We use 2 to ensure it is not the default. This could be any number that isn't 1.0f
    	mat4 m(2.0f);
		glm::mat4 matrix = instance->push(m);

		//Check to ensure we have got a new matrix
		REQUIRE(&matrix != &m);
		//Checks to ensure we have got a copy with the same values
		REQUIRE(matrix[0][0] == 2.0f);
		//Checks we can change the new one without affecting the previous
		matrix[0][0] = -1.0f;
		REQUIRE(m[0][0] != 1.0f);
	}
    SECTION("matrix should return last matrix on pop"){
    	using namespace glm;
    	mat4 m(2.0f);
		glm::mat4 matrix = instance->push(m);
		matrix[0][0] = -1.0f;
    	mat4 b = instance->pop();
		//They should now be the same
		//b should be the same as m, and matrix should be unique
		REQUIRE(&matrix != &b);
		REQUIRE(b[0][0] == 2.0f);
    }
	SECTION("stack should keep reference to matrices out of scope"){
		using namespace glm;

		//We should be able to push all of these onto the stack
		mat4 a(-1.0f);
		instance->push(a);
		a = glm::mat4(2.0f);
		instance->push(a);
		a = glm::mat4(3.0f);
		instance->push(a);
		a = glm::mat4(4.0f);
		instance->push(a);
		a = glm::mat4(5.0f);
		instance->push(a);
		//We should be able to get at a with values of -1 even though it has fallen out of scope
	    REQUIRE(instance->pop()[0][0] == 5.0f);
	    REQUIRE(instance->pop()[0][0] == 4.0f);
	    REQUIRE(instance->pop()[0][0] == 3.0f);
	    REQUIRE(instance->pop()[0][0] == 2.0f);
	    REQUIRE(instance->pop()[0][0] == -1.0f);
	}
	
}
