#ifndef LUAE_SCRIPT_H
#define LUAE_SCRIPT_H
#include <lua/lua.hpp>
#include <string>

namespace Luae {
class Script {
	private:
		const char* scriptName;
		const char* sourceChunk;
		//Reference in lua's registry
		int ref;
		void loadScript();
		enum ScriptSource {
			SCRIPT_SOURCE_NONE,
			SCRIPT_SOURCE_FILE,
			SCRIPT_SOURCE_CHUNK
		};
		ScriptSource sourceType;
		void loadFileScript();
		void loadChunkScript();
	
	public:
		static Script* Load(const char* fileName);
		static Script* Load(const std::string fileName);
		static Script* Load(const char* name, const char* sourceChunk);
		Script();
		Script(const char* scriptName);
		~Script();
		const char* getScriptName();
		bool has(const char* functionName);
		bool call(const char* functionName);
		bool call(const char* functionName, int nargs, int nresults);
		void pop();
		void push();
};
	
} // namespace Luae

#endif
