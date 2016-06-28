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
	if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(0.0f, -1.0f, 0.0f));
	}else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}else if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(-0.1f, 0.0f, 0.0f));
	}else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_UP && action == GLFW_REPEAT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -1.0f));
	}else if(key == GLFW_KEY_DOWN && action == GLFW_REPEAT && mods == 0){
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
/*
 * 	Our heightmap test will compose of the triangles: 
 * 	Each dot is a vertex
 * 	Arrows represent direction of edge, ? is down
 * 	. <	.. < .
 *  ?   ^?   ^
 * 	. >	.. > .
 * 	.	.
 *
 * 	.	.
 *
 */
	GLfloat heightMapTestVertices[] = {
		-1.0f, 1.0f,0.0f,
		-1.0f, 0.0f,0.0f,
		0.0f,0.0f,0.0f,
		1.0f, 0.0f,0.0f,
		0.0f, 1.0f,0.0f,
		1.0f, 1.0f,0.0f,
		0.0f, -1.0f,0.0f,
		-1.0f, -1.0f,0.0f
	};
	/*
	GLfloat triangle_one_vertices[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 100.0f, 1.0f,
		100.0f, 0.0f, 1.0f,
			};


	GLuint triangle_one_indices[] = {
		//Front face
		0, 2, 1
	};
	*/
	HeightmapName::HeightmapSettings heightmapSettings;

	heightmapSettings.widthDensity = 3;
	heightmapSettings.origin = glm::vec3(0.0f, 2.0f, -2.0f);
	
	HeightmapName::Heightmap heightmap(heightmapSettings);
	heightmap.build(heightmapSettings);
	GLfloat vertices[12];
	GLuint indices[6];

	/*
	float squareOrigin[] = {0.0f, 2.0f, -2.0f};

	vertices[0] = squareOrigin[0];
	vertices[1] = squareOrigin[1];
	vertices[2] = squareOrigin[2];

	vertices[3] = squareOrigin[0] + 1.0f;
	vertices[4] = squareOrigin[1] + 0.0f;
	vertices[5] = squareOrigin[2] + 0.0f;

	vertices[6] = squareOrigin[0] + 1.0f;
	vertices[7] = squareOrigin[1] + 0.0f;
	vertices[8] = squareOrigin[2] + 1.0f;

	vertices[9] = squareOrigin[0] + 0.0f;
	vertices[10] = squareOrigin[1] + 0.0f;
	vertices[11] = squareOrigin[2] + 1.0f;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
	*/

	GLfloat triangle_two_vertices[] = {
		0.0f, 0.2f, 1.0f,
		0.2f, 0.0f, 1.0f,
		0.2f, 0.2f, 1.0f
	};

	GLuint triangle_two_indices[] = {
		0,1,2
	};

	triangle.setVertices(vertices, sizeof(vertices) / sizeof(GLfloat));
	triangle.setIndices(indices, sizeof(indices) / sizeof(GLuint));
	//triangle.buildStatic();

	triangle_two.setVertices(triangle_two_vertices, sizeof(triangle_two_vertices) / sizeof(GLfloat));
	triangle_two.setIndices(triangle_two_indices, sizeof(triangle_two_indices) / sizeof(GLuint));
	//triangle_two.buildStatic();
	
	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");

	triangle.setShaderLocations(vertShaderLocation);
	triangle_two.setShaderLocations(vertShaderLocation);
	heightmap.setShaderLocations(vertShaderLocation);

	triangle.translate(glm::vec3(-1.0f, 0.0f, 0.0f));

	glViewport(0,0,VisualContext::width, VisualContext::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	
    while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));

//		triangle.update(&logicContext);
//		triangle.draw(&logicContext);
		heightmap.update(&logicContext);
		heightmap.draw(&logicContext);
		//triangle_two.update(&logicContext);
		//triangle_two.draw(&logicContext);
				 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
