#include "polygon.hpp"
#include <catch.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"
#include "visualcontext.hpp"
#include "terrian_config.hpp"
using namespace Terrian_Prototype;
//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}
TEST_CASE("Polygon initialization"){
	struct LogicContext logicContext;
	GLFWwindow *window = VisualContext::CreateGLFWWindow(key_callback);
	GLuint shader_program = VisualContext::make_shader_program(concat(xstr(SHADERS_DIR), "/shader.vert"), concat(xstr(SHADERS_DIR), "/shader.frag"));
    glUseProgram(shader_program);
    GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
    GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
	VisualContext::projection_matrix = glm::perspective(VisualContext::view_angle, VisualContext::aspect_ratio, VisualContext::z_near, VisualContext::z_far);

	logicContext.uloc_modelview = uloc_modelview;

	GLfloat triangle_one_vertices[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 100.0f, 1.0f,
		100.0f, 0.0f, 1.0f,
			};


	GLuint triangle_one_indices[] = {
		//Front face
		0, 2, 1
	};

	GLfloat triangle_two_vertices[] = {
		0.0f, 0.2f, 1.0f,
		0.2f, 0.0f, 1.0f,
		0.2f, 0.2f, 1.0f
	};

	GLuint triangle_two_indices[] = {
		0,1,2
	};

	SECTION("Vertices should only store reference"){
		Geometry::Polygon triangle;
		triangle.setVertices(triangle_one_vertices, sizeof(triangle_one_vertices) / sizeof(GLfloat));

		REQUIRE(triangle.getVertices() == &triangle_one_vertices[0]);
		triangle.setVertices(triangle_two_vertices, sizeof(triangle_two_vertices) / sizeof(GLfloat));
		REQUIRE(triangle.getVertices() != &triangle_one_vertices[0]);
	}
	SECTION("Indices should only store reference"){
		Geometry::Polygon triangle;
		triangle.setIndices(triangle_one_indices, sizeof(triangle_one_indices) / sizeof(GLuint));
	}
	SECTION("indicesSize should be the amount of triangles to draw"){
	} 
	SECTION("Model matrix should start as identity matrix"){
	}
	glfwDestroyWindow(window);

	glfwTerminate();

}

TEST_CASE("Polygon use"){
	SECTION("Model matrix should reset after drawing"){
	}
	SECTION("Translating should chang the model matrix"){
	}
	SECTION("buildStatic should allocate opengl drawing states"){
		//triangle.buildStatic();
	}
	SECTION("draw should bind and un-bind opengl buffers"){
	}
}
