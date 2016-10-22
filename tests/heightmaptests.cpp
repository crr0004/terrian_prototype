#include "heightmap.hpp"
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"
#include "visualcontext.hpp"
#include "terrian_config.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <catch.hpp>
#include <stdio.h>
using namespace Terrian_Prototype;
//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second


TEST_CASE("Heightmap"){

	GLuint* indices = new GLuint[54];
	GLfloat* vertices = new GLfloat[27];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;

	indices[6] = 1;
	indices[7] = 4;
	indices[8] = 5;
	indices[9] = 5;
	indices[10] = 3;
	indices[11] = 1;

	indices[12] = 12;
	indices[13] = 18;
	indices[14] = 21;
	indices[15] = 21;
	indices[16] = 15;
	indices[17] = 12;

	indices[18] = 24;
	indices[19] = 27;
	indices[20] = 1;
	indices[21] = 1;
	indices[22] = 0;
	indices[23] = 24;

	indices[24] = 27;
	indices[29] = 27;	
	Heightmap heightmap(vertices, indices);

	SECTION("getIndexOfSquare"){

		int s0 = heightmap.getIndexOfSquare(1);
		REQUIRE(s0 == 0);
		int s3 = heightmap.getIndexOfSquare(3);
		REQUIRE(s3 == 12);
		int s5 = heightmap.getIndexOfSquare(5);
		REQUIRE(s5 == 27);
	}
	SECTION("getIndexOfSquareVertex"){
		int v3 = heightmap.getIndexOfSquareVertex(3, 3);
		int v2 = heightmap.getIndexOfSquareVertex(3, 2);
		int v1 = heightmap.getIndexOfSquareVertex(3, 1);
		//21 is the start of the eighth vertex
		REQUIRE(v3 == 21);
		REQUIRE(v2 == 18);
		REQUIRE(v1 == 12);

	}

}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}
/*
TEST_CASE("Heightmap Collision"){
	struct LogicContext logicContext;
	GLFWwindow *window = VisualContext::CreateGLFWWindow(key_callback);
	GLuint shader_program = VisualContext::make_shader_program(concat(xstr(SHADERS_DIR), "/shader.vert"), concat(xstr(SHADERS_DIR), "/shader.frag"));
	glUseProgram(shader_program);
	GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
	GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

	/* Compute the projection matrix 
	VisualContext::projection_matrix = glm::perspective(VisualContext::view_angle, VisualContext::aspect_ratio, VisualContext::z_near, VisualContext::z_far);

	logicContext.uloc_modelview = uloc_modelview;
    /* Set the camera position  
	logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -7.0f));
	logicContext.modelview = glm::rotate(logicContext.modelview, 1.57f, glm::vec3(-1.0f, 0.0f, 0.0f));

	SECTION("getIndexOfSquareIntersectingLine"){
		glm::vec4 a = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f) * logicContext.modelview;
		glm::vec4 b = glm::vec4(0.0f, 0.0f, -20.0f, 0.0f) * logicContext.modelview;
		HeightmapSettings heightmapSettings;

		heightmapSettings.widthDensity = 10;
		heightmapSettings.origin = glm::vec3(0.0f, 0.0f, 0.0f);

		Heightmap heightmap(heightmapSettings);
		heightmap.build(heightmapSettings);

		REQUIRE( heightmap.getIndexOfSquareIntersectingLine(glm::vec3(a), glm::vec3(b)) == 0);

	}
}
*/
