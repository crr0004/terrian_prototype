#ifndef VISUALCONTEXT_H
#define VISUALCONTEXT_H 1
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class VisualContext {
	public:
		static GLFWwindow* CreateWindow(GLFWkeyfun key_callback);
		static GLuint make_shader_program(const char* vs_text, const char* fs_text);
		static GLfloat view_angle;
		static int width;
		static int height;
		/* Frustum configuration */
		static GLfloat aspect_ratio;
		static GLfloat z_near;
		static GLfloat z_far;

		static glm::mat4 projection_matrix;
	private:
		static void error_callback(int error, const char* description);
		static void check_error();
		/* Creates a shader object of the specified type using the specified text
		*/
		static GLuint make_shader(GLenum type, const char* text); 

		/* Creates a program object using the specified vertex and fragment text
		*/
		static char* readfile(const char* filePath);
};

#endif /* ifndef VISUALCONTEXT_H */
