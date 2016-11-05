#ifndef LUAE_SCRIPT_H
#define LUAE_SCRIPT_H
#include <lua/lua.hpp>
#include <string>

namespace Luae {
class Script {
	private:
		const char* scriptName;
		void loadScript();
	
	public:
		Script();
		Script(const char* scriptName);
		~Script();
		const char* getScriptName();
		static Script* Load(const char* fileName);
		static Script* Load(const std::string fileName);
		bool has(const char* functionName);
		bool call(const char* functionName);
		bool call(const char* functionName, int nargs, int nresults);
};
	
} // namespace Luae

#endif
