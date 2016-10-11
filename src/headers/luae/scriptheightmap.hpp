#ifndef SCRIPTHEIGHTMAP_H
#define SCRIPTHEIGHTMAP_H
#include <lua/lua.hpp>
#include "heightmap.hpp"
namespace Terrian_Prototype{
	namespace Luae {
		class ScriptHeightMap {
			public:
				static ScriptHeightMap* instance();
			protected:
				ScriptHeightMap();
				~ScriptHeightMap();
			private:
				static ScriptHeightMap* _instance;
		};
	} // namespace Luae

}
#endif
