#ifndef LUAE_SCRIPT_H
#define LUAE_SCRIPT_H
#include <lua/lua.hpp>

namespace Luae {
class Script {
	private:
		const char* scriptName;
	
	public:
		Script();
		Script(const char* scriptName);
		~Script();
		static Script* Load(const char* fileName);
		bool has(const char* functionName);
		void call(const char* functionName);
};
	
} // namespace Luae

#endif
