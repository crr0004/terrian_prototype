#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/LU>

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>


static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static GLfloat z = 0.0f;
static int width = 800;
static int height = 600;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
	}else if(key == GLFW_KEY_UP && action == GLFW_PRESS){
		z += 0.001f;
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

    window = glfwCreateWindow(width, height, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);


    glewExperimental=true;
	GLenum err=glewInit(); 
	if(err!=GLEW_OK) { //Problem: glewInit failed, something is seriously wrong. 
        fprintf(stderr, "ERROR: Unable to init glew\n");
	}
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

/* Frustum configuration */
static GLfloat view_angle = 90.0f;
static GLfloat aspect_ratio = 4.0f/3.0f;
static GLfloat z_near = 1.0f;
static GLfloat z_far = 100.f;


static Eigen::Matrix<float, 4, 4> projection_matrix;
static Eigen::Matrix<float, 4, 4> modelview_matrix;

int main(void)
{

	GLFWwindow *window = CreateWindow();
	GLuint shader_program = make_shader_program(readfile("shader.vert"), readfile("shader.frag"));
    glUseProgram(shader_program);
    GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
    GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

    /* Compute the projection matrix */
    float f = 1.0f / tanf(view_angle / 2.0f);
    projection_matrix(0)  = f / aspect_ratio;
    projection_matrix(5)  = f;
    projection_matrix(10) = (z_far + z_near)/ (z_near - z_far);
    projection_matrix(11) = -1.0f;
    projection_matrix(14) = 2.0f * (z_far * z_near) / (z_near - z_far);
	
    glUniformMatrix4fv(uloc_project, 1, GL_FALSE, projection_matrix.data());

    /* Set the camera position  */
	modelview_matrix = modelview_matrix.setIdentity();
	modelview_matrix(14) = -1;
	std::cout << modelview_matrix << std::endl;
    glUniformMatrix4fv(uloc_modelview, 1, GL_FALSE, modelview_matrix.data());


	GLuint vboID[2];
	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
			};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	glGenBuffers(2, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");

	glViewport(0,0,width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	
    while (!glfwWindowShouldClose(window))
    {


		glClear(GL_COLOR_BUFFER_BIT);
		glEnableVertexAttribArray(vertShaderLocation);
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
		glVertexAttribPointer(
				vertShaderLocation,
				3, //size of attribute
				GL_FLOAT,
				GL_FALSE,
				0, //stride
				(void*)0 //Pointer to the off of the first component of the first element
				);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
		glDrawElements(
				GL_TRIANGLES,
				6, //Amount of vertices to draw
				GL_UNSIGNED_INT,
				(void*)0
				);

		glDisableVertexAttribArray(vertShaderLocation);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
