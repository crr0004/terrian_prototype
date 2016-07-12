#include "visualcontext.h"
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "gldebug.h"

GLfloat VisualContext::view_angle = 45.0f;
int VisualContext::width = 800;
int VisualContext::height= 600;
GLfloat VisualContext::aspect_ratio = 4.0f/3.0f;
GLfloat VisualContext::z_near = 0.00001f;
GLfloat VisualContext::z_far = 10000.f;

glm::mat4 VisualContext::projection_matrix;

void VisualContext::error_callback(int error, const char* description) {
    fputs(description, stderr);
}
void VisualContext::check_error(){
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
		fprintf(stderr, "OpenGL Error: %s\n", error);
		}
		//
}

/* Creates a shader object of the specified type using the specified text
 */
GLuint VisualContext::make_shader(GLenum type, const char* text) {
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
GLuint VisualContext::make_shader_program(const char* vs_path, const char* fs_path) {
	const char* vs_text = readfile(vs_path);
	const char* fs_text = readfile(fs_path);
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

GLFWwindow* VisualContext::CreateWindow(GLFWkeyfun key_callback){
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

char* VisualContext::readfile(const char* filePath){

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
