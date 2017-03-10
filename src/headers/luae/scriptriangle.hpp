#ifndef SCRIPTRIANGLE_H
#define SCRIPTRIANGLE_H
#include <lua/lua.hpp>
namespace Luae{
		class ScriptTriangle {
			public:
				static void AddToLib();
				static int Create(lua_State* l);
				static int GetTriangleVerticesAsTable(lua_State* l);
				static int Translate(lua_State*);
		};
	} // namespace Luae

#endif
