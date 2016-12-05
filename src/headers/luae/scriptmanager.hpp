#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
#include <lua/lua.hpp>
namespace Luae{
class ScriptManager{
	public:
		static ScriptManager* instance();
		lua_State* getState();
		void NewLib(const struct luaL_Reg lib[], const char* name);
		void NewMetaLib(const struct luaL_Reg lib[], const char* name);
	protected:
		ScriptManager();
		~ScriptManager();
	private:
		static ScriptManager* _instance;
		lua_State* state;

};
}//Luae namespace

#endif // !SCRIPTMANAGERSINGLETON_H
