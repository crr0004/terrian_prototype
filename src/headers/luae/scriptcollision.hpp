#ifndef SCRIPTCOLLISION_H
#define SCRIPTCOLLISION_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <lua/lua.hpp>
namespace Luae {
	class ScriptCollision {
		public:
			static void AddToLib();
			static int GetPointFromRay(lua_State*);
	};
}
#endif
