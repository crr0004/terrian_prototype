#include "visualcontext.hpp"
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <limits.h>
#include "gldebug.hpp"

GLfloat VisualContext::view_angle = 45.0f;
int VisualContext::width = 800;
int VisualContext::height= 600;
GLfloat VisualContext::aspect_ratio = 4.0f/3.0f;
GLfloat VisualContext::z_near = 0.0001f;
GLfloat VisualContext::z_far = 1000.f;

glm::mat4 VisualContext::projection_matrix;

void VisualContext::error_callback(int error, const char* description) {
    fputs(description, stderr);
}
void VisualContext::check_error(){
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		const char* error = "";

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

GLFWwindow* VisualContext::CreateGLFWWindow(GLFWkeyfun key_callback){
    GLFWwindow* window;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);


	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);

    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


	//glEnable(GL_DEBUG_OUTPUT);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);



	GLint v = 0;
	glGetIntegerv(GL_CONTEXT_FLAGS, &v);
	if(v & GL_CONTEXT_FLAG_DEBUG_BIT){
		printf("%s %d\n", "OpenGL debugging enabled", v);
		glDebugMessageCallback(glDebug::myCallback, (GLvoid*)0);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
	}else{
		printf("%s\n", "OpenGL debugging disabled");
	}
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

	glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
	return window;
}

char* VisualContext::readfile(const char* filePath){
	char *buffer = NULL;
	int string_size, read_size;
	FILE *handler = fopen(filePath, "rb");

	if (handler)
	{
		// Seek the last byte of the file
		fseek(handler, 0, SEEK_END);
		// Offset from the first to the last byte, or in other words, filesize
		string_size = ftell(handler);
		// go back to the start of the file
		rewind(handler);

		// Allocate a string that can hold it all
		//buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
		buffer = new char[string_size + 1];

		// Read it all in one operation
		read_size = (int)fread(buffer, sizeof(char), string_size, handler);

		// fread doesn't set it so put a \0 in the last position
		// and buffer is now officially a string
		buffer[string_size] = '\0';

		if (string_size != read_size)
		{
			// Something went wrong, throw away the memory and set
			// the buffer to NULL
			printf("Shader %s\n", buffer);
			fprintf(stderr, "\
Unable to open file at %s\t error code %d\n\
Expected %d characters, got %d characters\n",\
		       	filePath, ferror(handler), string_size, read_size);
			delete[] buffer;
			buffer = NULL;
		}

		// Always remember to close the file.
		fclose(handler);
	}else{
		fprintf(stderr, "Couldn't open file %s\n", filePath);

	}

	return buffer;
}
