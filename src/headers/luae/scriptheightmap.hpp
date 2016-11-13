#ifndef SCRIPTHEIGHTMAP_H
#define SCRIPTHEIGHTMAP_H
#include <lua/lua.hpp>
#include "heightmap.hpp"
namespace Terrian_Prototype{
	namespace Luae {
		class ScriptHeightMap {
			public:
				static void AddToLib();
				static int Build(lua_State* l);

		};
	} // namespace Luae

}
#endif
