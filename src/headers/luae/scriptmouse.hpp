#ifndef SCRIPTMOUSE_H
#define SCRIPTMOUSE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lua/lua.hpp>
#include "logiccontext.hpp"
namespace Luae{
		class ScriptMouse {
			public:
				static void AddToLib();
				static int GetMouseCords(lua_State*);
				static int getLeftMouseButton(lua_State*);
				static void SetWindow(GLFWwindow*);
				static void SetLogicContex(LogicContext*);
			private:
				static GLFWwindow* window;
				static LogicContext* logicContext;
		};
}
#endif
