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

static struct LogicContext logicContext;


static Polygon triangle;
static Polygon triangle_two;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		printf("Triangle 1 Model Matrix: %s\n", glm::to_string(logicContext.modelview * *triangle.getModelMatrix()).c_str());
	}
	if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(0.0f, -1.0f, 0.0f));
	}else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}else if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(-0.1f, 0.0f, 0.0f));
	}else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_UP && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::scale(logicContext.modelview, glm::vec3(0.9f,0.9f,0.9f));
	}else if(key == GLFW_KEY_DOWN && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::scale(logicContext.modelview, glm::vec3(1.1f,1.1f,1.1f));
	}else if(key == GLFW_KEY_UP && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -1.0f));
	}else if(key == GLFW_KEY_DOWN && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, 1.0f));
	}
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
	logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -7.0f));
	logicContext.modelview = glm::rotate(logicContext.modelview, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

//Triangle test vertices
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

	triangle.setVertices(triangle_one_vertices, sizeof(triangle_one_vertices) / sizeof(GLfloat));
	triangle.setIndices(triangle_one_indices, sizeof(triangle_one_indices) / sizeof(GLuint));
	triangle.buildStatic();

	triangle_two.setVertices(triangle_two_vertices, sizeof(triangle_two_vertices) / sizeof(GLfloat));
	triangle_two.setIndices(triangle_two_indices, sizeof(triangle_two_indices) / sizeof(GLuint));
	triangle_two.buildStatic();
	
	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");

	triangle.setShaderLocations(vertShaderLocation);
	triangle_two.setShaderLocations(vertShaderLocation);

	triangle.translate(glm::vec3(-1.0f, 0.0f, 0.0f));

//Generate a polygon made up triangles
	struct HeightMapSettings heightMapSettings;
	//Size of map in coordinate system
	heightMapSettings.width = 500;
	heightMapSettings.depth = 500;

	//How many squares (really triangles*2) between map extents.
	//500,500 means a density of 1
	heightMapSettings.widthDensity = 500;
	heightMapSettings.depthDensity = 500;

	//Where to place the center of the map in the local coordinate system
	heightMapSettings.origin = glm::vec3(0.0f,0.0f,0.0f);

	HeightMap heightMap;
	heightMap.build(heightMapSettings);
	heightMap.setShaderLocations(vertShaderLocation);

	glViewport(0,0,VisualContext::width, VisualContext::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	
    while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));

		heightMap.update(&logicContext);
		heightMap.draw(&logicContext);

		triangle.update(&logicContext);
		triangle.draw(&logicContext);
		triangle_two.update(&logicContext);
		triangle_two.draw(&logicContext);
				 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
