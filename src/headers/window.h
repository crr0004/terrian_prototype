#ifndef WINDOW_H
#define WINDOW_H
#endif
#include <GLFW/glfw3.h>
class Window{

	private:
		GLFWwindow *window;
	public:
	char *title;
	int width;
	int height;
	bool create();
	bool shouldClose();


};
