#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdlib.h>

#include "matrixstacksingleton.h"
#include "polygon.h"
#include "logiccontext.h"
#include "visualcontext.h"
#include "heightmap.h"
#include "line.h"

static struct LogicContext logicContext;
static glm::vec3 ray_world;


static Polygon triangle;
static Polygon triangle_two;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		printf("Triangle 1 Model Matrix: %s\n", glm::to_string(ray_world).c_str());
	}
	if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(0.0f, -1.0f, 0.0f));
	}
	else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}
	else if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(-0.1f, 0.0f, 0.0f));
	}
	else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_UP && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -1.0f));
	}
	else if(key == GLFW_KEY_DOWN && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else if(key == GLFW_KEY_UP && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
	}
	else if(key == GLFW_KEY_DOWN && mods == GLFW_MOD_SHIFT){
					logicContext.modelview = glm::rotate(logicContext.modelview, -0.1f, glm::vec3(1.0f, 0.0f, 0.0f));

		}
}
static void calcWorldPickRay(GLFWwindow *window){
		//Build ray from mouse
		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		glm::vec4 ray_clip = glm::vec4((2.0f * mouseX) / VisualContext::width - 1.0f, 1.0f - (2.0f * mouseY) / VisualContext::height, -1.0f, 1.0f);

		glm::vec4 ray_eye = glm::inverse(VisualContext::projection_matrix) * ray_clip;
		ray_eye.z = -1.0f;
		ray_eye.w = 1.0f;

		ray_world = glm::vec3(glm::inverse(logicContext.modelview) * ray_eye);
//		ray_world = glm::normalize(ray_world);

}

int main(void) {
	
	GLFWwindow *window = VisualContext::CreateWindow(key_callback);
	GLuint shader_program = VisualContext::make_shader_program("shaders/shader.vert", "shaders/shader.frag");
    glUseProgram(shader_program);
    GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
    GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
	VisualContext::projection_matrix = glm::perspective(VisualContext::view_angle, VisualContext::aspect_ratio, VisualContext::z_near, VisualContext::z_far);

	logicContext.uloc_modelview = uloc_modelview;

    /* Set the camera position  */
	logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -20.0f));
	logicContext.modelview = glm::rotate(logicContext.modelview, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));

	HeightmapNS::HeightmapSettings heightmapSettings;

	heightmapSettings.widthDensity = 10;
	heightmapSettings.origin = glm::vec3(0.0f, 0.0f, 0.0f);
	
	HeightmapNS::Heightmap heightmap(heightmapSettings);
	heightmap.build(heightmapSettings);

	GLfloat triangle_two_vertices[] = {
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	GLuint triangle_two_indices[] = {
		0,1,2
	};

	triangle.setVertices(triangle_two_vertices, sizeof(triangle_two_vertices) / sizeof(GLfloat));
	triangle.setIndices(triangle_two_indices, sizeof(triangle_two_indices) / sizeof(GLuint));
triangle.buildStatic();

	
	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");

	triangle.setShaderLocations(vertShaderLocation);
	triangle_two.setShaderLocations(vertShaderLocation);
	heightmap.setShaderLocations(vertShaderLocation);

	glViewport(0,0,VisualContext::width, VisualContext::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	Line worldLine;
	worldLine.buildStatic();
	worldLine.setShaderLocations(vertShaderLocation);
	Line worldLine2;
	worldLine2.buildStatic();
	worldLine2.setShaderLocations(vertShaderLocation);
	//worldLine.rotate(glm::vec3(1.0f, 0.0f, 0.0f), 1.57f);
	
    while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));

		triangle.update(&logicContext);
		triangle.draw(&logicContext);
//		heightmap.update(&logicContext);
//		heightmap.draw(&logicContext);
		calcWorldPickRay(window);
		worldLine.setStartEnd(ray_world, glm::vec3(0.0f, 0.0f, -100.0f));
		worldLine.update(&logicContext);
		worldLine.draw(&logicContext);
		worldLine2.setStartEnd(ray_world, glm::vec3(10.0f, 0.0f, 0.0f));
	worldLine2.update(&logicContext);
	worldLine2.draw(&logicContext);

		//triangle_two.update(&logicContext);
		//triangle_two.draw(&logicContext);
				 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
