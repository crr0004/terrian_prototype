#ifndef SCRIPTHEIGHTMAP_H
#define SCRIPTHEIGHTMAP_H
#include <lua/lua.hpp>
#include "heightmap.hpp"
namespace Luae{
		class ScriptHeightMap {
			public:
				static void AddToLib();
				static int Build(lua_State* l);
				static int GetSettings(lua_State* l);
			private:
				HeightmapSettings settings;
		};
	} // namespace Luae

#endif
