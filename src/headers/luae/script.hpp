#ifndef LUAE_SCRIPT_H
#define LUAE_SCRIPT_H
#include <lua/lua.hpp>

namespace Luae {
class Script {
	
	public:
		Script();
		~Script();
		static Script* Load(const char* fileName);
		bool has(const char* functionName);
		void call(const char* functionName);
};
	
} // namespace Luae

#endif
