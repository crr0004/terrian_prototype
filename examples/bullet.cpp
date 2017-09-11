#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <lua/lua.hpp>
#include <vector>
#include <fmt/format.h>
#include <btBulletDynamicsCommon.h>

#include "terrian_config.hpp"
#include "matrixstacksingleton.hpp"
#include "polygon.hpp"
#include "logiccontext.hpp"
#include "visualcontext.hpp"
#include "heightmap.hpp"
#include "line.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "addtodrawqueue.hpp"
#include "luae/script.hpp"
#include "luae/scriptmanager.hpp"
#include "luae/scriptheightmap.hpp"
#include "luae/scriptriangle.hpp"
#include "luae/scriptmouse.hpp"

#include "collision/simpleworld.hpp"
#include "collision/spherecollider.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second

static struct LogicContext logicContext;
static glm::vec3 ray_world;


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	glm::vec3 up = glm::vec3(glm::vec4(0.0, 1.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 down = glm::vec3(glm::vec4(0.0, -1.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 left = glm::vec3(glm::vec4(-1.0, 0.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 right = glm::vec3(glm::vec4(1.0, 0.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 back = glm::vec3(glm::vec4(0.0, 0.0, -1.0, 1.0) * logicContext.modelview);
	glm::vec3 forward = glm::vec3(glm::vec4(0.0, 0.0, 1.0, 1.0) * logicContext.modelview);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		printf("Triangle 1 Model Matrix: %s\n", glm::to_string(logicContext.modelview).c_str());
	}
	if(key == GLFW_KEY_R && action == GLFW_RELEASE){
		logicContext.modelview = glm::mat4();

	}
	if(key == GLFW_KEY_LEFT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, up);
	}
	else if(key == GLFW_KEY_RIGHT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, down);
	}
	else if(key == GLFW_KEY_LEFT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, left * 0.1f);
	}
	else if(key == GLFW_KEY_RIGHT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, right * 0.1f);
	}
	if(key == GLFW_KEY_UP && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, up * 0.1f);
	}
	else if(key == GLFW_KEY_DOWN && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, down * 0.1f);
	}
	else if(key == GLFW_KEY_UP && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, left);
	}
	else if(key == GLFW_KEY_DOWN && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, right);

	}else if(key == GLFW_KEY_UP && mods == GLFW_MOD_CONTROL){
		logicContext.modelview = glm::translate(logicContext.modelview, back * 0.1f);
	}else if(key == GLFW_KEY_DOWN && mods == GLFW_MOD_CONTROL){
		logicContext.modelview = glm::translate(logicContext.modelview, forward * 0.1f);
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

	//Setup for windows
	GLFWwindow *window = VisualContext::CreateGLFWWindow(key_callback);
	GLuint shader_program = VisualContext::make_shader_program(concat(xstr(SHADERS_DIR), "/shader.vert"), concat(xstr(SHADERS_DIR), "/shader.frag"));
	glUseProgram(shader_program);
	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");
	GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
	GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

	/* Compute the projection matrix */
	VisualContext::projection_matrix = glm::perspective(VisualContext::view_angle, VisualContext::aspect_ratio, VisualContext::z_near, VisualContext::z_far);
	logicContext.uloc_modelview = uloc_modelview;

	/* Set the camera position  */
	logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -20.0f));
	logicContext.modelview = glm::rotate(logicContext.modelview, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
	glViewport(0,0,VisualContext::width, VisualContext::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//END Setup for windows


	//Create a draw queue
	std::vector<Geometry::Polygon*> drawQueue;
	//Draw queue gets added to a command so other parts of code can easily add
	//to queue
	AddToDrawQueueCommand::SetQueue(&drawQueue);
	//Add lua adapters to lua namespace
	Luae::ScriptTriangle::AddToLib();
	//ScriptMouse is pretty broken at the moment
	/*
	Luae::ScriptMouse::AddToLib();
	Luae::ScriptMouse::SetWindow(window);
	Luae::ScriptMouse::SetLogicContex(&logicContext);
	*/

	Geometry::Line worldLine;
	worldLine.buildStatic();
	worldLine.setShaderLocations(vertShaderLocation);
	worldLine.setLogicContext(&logicContext);

	Geometry::Circle circle;
	Geometry::Circle circle2;

	circle.setLogicContext(&logicContext);
	circle.setShaderLocations(vertShaderLocation);
	circle.buildStatic();

	circle2.setLogicContext(&logicContext);
	circle2.setShaderLocations(vertShaderLocation);
	circle2.buildStatic();

	lua_State* l = Luae::ScriptManager::instance()->getState();
	Luae::Script* script = Luae::Script::Load("example_bullet.lua");
	script->call("init");
	/**
	 * SAMPLE
	 * How you add to draw queue
	 * This is currently how script adapters do it

		lua_getglobal(l, "triangle");
		Triangle* triangle = *(Triangle**)lua_touserdata(l,-1);
		drawQueue.push_back(triangle);
		AddToDrawQueueCommand addTriangle(Geometry::Polygon);
		addTriangle.execute();
	 
	 * END SAMPLE
	*/

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();	

	//Enables antialiasing
	glEnable(GL_MULTISAMPLE);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));


		calcWorldPickRay(window);
		glm::vec3 rayWordEndPoint = glm::vec3(glm::vec4(0.0f, 0.0f, -100.0f, 1.0f) * logicContext.modelview);

		worldLine.setStartEnd(ray_world, rayWordEndPoint);
		worldLine.update();
		worldLine.draw();

		circle.update();
		circle.draw();

		circle2.update();
		circle2.draw();

		script->call("update");

		//triangle->update(&logicContext);
		//triangle->draw(&logicContext);

		for(std::vector<Geometry::Polygon*>::iterator drawHost = drawQueue.begin();
				drawHost != drawQueue.end();
				drawHost++){
			glDisable(GL_CULL_FACE);
			/**
			 * TODO This is okay for now, however the logicContext will become
			 * the shader from a shader manager/factory 
			 * so each object should set it, itself.
			 * (*drawHost)->setLogicContext(&logicContext);
			 */
			(*drawHost)->setLogicContext(&logicContext);

			(*drawHost)->update();
			(*drawHost)->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete script;
	MatrixStackSingleton::Destroy();

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
