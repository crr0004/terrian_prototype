#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "gldebug.h"
#include "matrixstacksingleton.h"
#include "polygon.h"
#include "logicstate.h"

static struct LogicState logicState;

static int width = 800;
static int height = 600;
/* Frustum configuration */
static GLfloat view_angle = 45.0f;
static GLfloat aspect_ratio = 4.0f/3.0f;
static GLfloat z_near = 0.00001f;
static GLfloat z_far = 100.f;

static glm::mat4 projection_matrix;
static glm::mat4 modelview_matrix;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void check_error(){
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		const char* error;

		switch(err) {
			case GL_INVALID_OPERATION:      error="INVALID_OPERATION";      break;
			case GL_INVALID_ENUM:           error="INVALID_ENUM";           break;
			case GL_INVALID_VALUE:          error="INVALID_VALUE";          break;
			case GL_OUT_OF_MEMORY:          error="OUT_OF_MEMORY";          break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:  error="INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		std::cerr << "OpenGL error: " << error << std::endl;
		}
		//
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == 0){
		modelview_matrix = glm::rotate(modelview_matrix, 0.1f, glm::vec3(0.0f, -1.0f, 0.0f));
	}else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == 0){
		modelview_matrix = glm::rotate(modelview_matrix, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f));
	}else if(key == GLFW_KEY_LEFT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		modelview_matrix = glm::translate(modelview_matrix, glm::vec3(-0.1f, 0.0f, 0.0f));
	}else if(key == GLFW_KEY_RIGHT && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.1f, 0.0f, 0.0f));
	}
	if(key == GLFW_KEY_UP && action == GLFW_REPEAT && mods == 0){
		modelview_matrix = glm::scale(modelview_matrix, glm::vec3(0.9f,0.9f,0.9f));
	}else if(key == GLFW_KEY_DOWN && action == GLFW_REPEAT && mods == 0){
		modelview_matrix = glm::scale(modelview_matrix, glm::vec3(1.1f,1.1f,1.1f));
	}else if(key == GLFW_KEY_UP && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, -0.1f));
	}else if(key == GLFW_KEY_DOWN && action == GLFW_REPEAT && mods == GLFW_MOD_SHIFT){
		modelview_matrix = glm::translate(modelview_matrix, glm::vec3(0.0f, 0.0f, 0.1f));
	}
}
/* Creates a shader object of the specified type using the specified text
 */
static GLuint make_shader(GLenum type, const char* text)
{
    GLuint shader;
    GLint shader_ok;
    GLsizei log_length;

    shader = glCreateShader(type);
    if (shader != 0)
    {
        glShaderSource(shader, 1, (const GLchar**)&text, NULL);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
        if (shader_ok != GL_TRUE)
        {
			char info_log[8192];
            fprintf(stderr, "ERROR: Failed to compile %s shader\n", (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex" );
            glGetShaderInfoLog(shader, 8192, &log_length,info_log);
            fprintf(stderr, "ERROR: \n%s\n\n", info_log);
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

/* Creates a program object using the specified vertex and fragment text
 */
static GLuint make_shader_program(const char* vs_text, const char* fs_text)
{
    GLuint program = 0u;
    GLint program_ok;
    GLuint vertex_shader = 0u;
    GLuint fragment_shader = 0u;
    GLsizei log_length;

    vertex_shader = make_shader(GL_VERTEX_SHADER, vs_text);
    if (vertex_shader != 0u)
    {
        fragment_shader = make_shader(GL_FRAGMENT_SHADER, fs_text);
        if (fragment_shader != 0u)
        {
            /* make the program that connect the two shader and link it */
            program = glCreateProgram();
            if (program != 0u)
            {
                /* attach both shader and link */
                glAttachShader(program, vertex_shader);
                glAttachShader(program, fragment_shader);
                glLinkProgram(program);
                glGetProgramiv(program, GL_LINK_STATUS, &program_ok);

                if (program_ok != GL_TRUE)
                {
					char info_log[8192];
                    fprintf(stderr, "ERROR, failed to link shader program\n");
                    glGetProgramInfoLog(program, 8192, &log_length, info_log);
                    fprintf(stderr, "ERROR: \n%s\n\n", info_log);
                    glDeleteProgram(program);
                    glDeleteShader(fragment_shader);
                    glDeleteShader(vertex_shader);
                    program = 0u;
                }
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Unable to load fragment shader\n");
            glDeleteShader(vertex_shader);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Unable to load vertex shader\n");
    }
	delete[] vs_text;
	delete[] fs_text;
    return program;
}

static GLFWwindow* CreateWindow(){
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);


	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	GLenum err=glewInit(); 
	if(err!=GLEW_OK) { //Problem: glewInit failed, something is seriously wrong. 
        fprintf(stderr, "ERROR: Unable to init glew\n");
	}

	glEnable(GL_DEBUG_OUTPUT);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	GLint v;
	glGetIntegerv(GL_CONTEXT_FLAGS, &v);
	if(v & GL_CONTEXT_FLAG_DEBUG_BIT){
		printf("%s %d\n", "OpenGL debugging enabled", v);
		glDebugMessageCallback(glDebug::myCallback, (GLvoid*)0);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	}else{
		printf("%s %d\n", "OpenGL debugging disabled", v);
	}
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
	return window;
}

static char* readfile(const char* filePath){

	using namespace std;
	streampos size;
	char * memblock;

	//ios:ate opens the file at the end so we can get the size of the file
	ifstream file (filePath, ios::in|ios::binary|ios::ate);
	if (file.is_open()){

		size = file.tellg();
		memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

	}else{
	   	fprintf(stderr, "Unable to open file at %s", filePath);
	}

	return memblock;
}

int main(void)
{

	GLFWwindow *window = CreateWindow();
	GLuint shader_program = make_shader_program(readfile("shaders/shader.vert"), readfile("shaders/shader.frag"));
    glUseProgram(shader_program);
    GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
    GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
	projection_matrix = glm::perspective(view_angle, aspect_ratio, z_near, z_far);

	logicState.modelview = modelview_matrix;

    /* Set the camera position  */
	logicState.modelview = glm::translate(logicState.modelview, glm::vec3(0.0f, 0.0f, -7.0f));
	logicState.modelview = glm::rotate(logicState.modelview, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	Polygon triangle;
	Polygon triangle_two;
//Triangle test vertices
	GLfloat triangle_one_vertices[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.1f, 1.0f,
		0.1f, 0.0f, 1.0f,
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

	triangle.translate(glm::vec3(0.0f, 0.0f, -7.0f));

	glViewport(0,0,width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	
    while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);

		triangle.update(&logicState);
		triangle_two.update(&logicState);

		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(projection_matrix));
		glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, glm::value_ptr(logicState.modelview));

		triangle.draw();
		triangle_two.draw();
				 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
