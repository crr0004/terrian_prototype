#include "luae/scriptmouse.hpp"
#include "luae/scriptmanager.hpp"
#include "luae/Utilities.hpp"
#include <fmt/format.h>
#include <glm/glm.hpp>
#include "visualcontext.hpp"
using namespace Luae;

GLFWwindow* ScriptMouse::window = 0;
LogicContext* ScriptMouse::logicContext = 0;
static const struct luaL_Reg LuaFunctions[] = {
	{"asCollideCircle", ScriptMouse::CircleCollision},
	{NULL, NULL}

};

void ScriptMouse::AddToLib(){
	ScriptManager::instance()->NewLib(LuaFunctions, "Mouse");
}

int ScriptMouse::CircleCollision(lua_State* l){
	double mouseX;
	double mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);
	glm::vec4 ray_clip = glm::vec4((2.0f * mouseX) / VisualContext::width - 1.0f, 1.0f - (2.0f * mouseY) / VisualContext::height, -1.0f, 1.0f);

	glm::vec4 ray_eye = glm::inverse(VisualContext::projection_matrix) * ray_clip;
	ray_eye.z = -1.0f;
	ray_eye.w = 1.0f;

	glm::vec3 ray_world = glm::vec3(glm::inverse(logicContext->modelview) * ray_eye);
	lua_createtable(l, 0, 3);
	lua_pushnumber(l, ray_world.x);
	lua_rawseti(l, -2, 1);
	lua_pushnumber(l, ray_world.y);
	lua_rawseti(l, -2, 2);
	lua_pushnumber(l, ray_world.z);
	lua_rawseti(l,-2,3);
	return 1;
}

void ScriptMouse::SetWindow(GLFWwindow* window){
	ScriptMouse::window = window;
}
void ScriptMouse::SetLogicContex(LogicContext* context){
	ScriptMouse::logicContext = context;
}
