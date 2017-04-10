#ifndef SCRIPTMANAGER_H
#define SCRIPTMANAGER_H
#include <lua/lua.hpp>
namespace Luae{
class ScriptManager{
	public:
		static ScriptManager* instance();
		static void Close();
		lua_State* getState();
		void NewLib(const struct luaL_Reg lib[], const char* name);
		void NewMetaLib(const struct luaL_Reg lib[], const char* name);
		void RestoreGlobalTable();
	protected:
		ScriptManager();
		~ScriptManager();
	private:
		static ScriptManager* _instance;
		lua_State* state;
		int globalTableRef;

};
}//Luae namespace

#endif // !SCRIPTMANAGERSINGLETON_H
