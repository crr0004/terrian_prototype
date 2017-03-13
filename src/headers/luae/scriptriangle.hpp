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
				static int SetVert1(lua_State*);
				static int SetVert2(lua_State*);
				static int SetVert3(lua_State*);
		};
	} // namespace Luae

#endif
