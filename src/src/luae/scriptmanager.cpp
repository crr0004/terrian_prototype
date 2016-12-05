#include "luae/scriptmanager.hpp"
#include <lua/lua.hpp>

using namespace Luae;
ScriptManager* ScriptManager::_instance = 0;


ScriptManager::ScriptManager(){
	state = luaL_newstate();
	luaL_openlibs(state);

}

ScriptManager::~ScriptManager(){
	lua_close(state);
}

lua_State* ScriptManager::getState() {
	return state;
}
void ScriptManager::NewMetaLib(const struct luaL_Reg lib[], const char* name){
	luaL_newmetatable(state, name);
	luaL_setfuncs(state, lib, 0);
	lua_setfield(state, -1, "__index");
}
void ScriptManager::NewLib(const struct luaL_Reg lib[], const char* name) {
	luaL_newlib(state, lib);
	lua_setglobal(state, name);
}


ScriptManager* ScriptManager::instance(){
	if(ScriptManager::_instance == 0){
		_instance = new ScriptManager();
	}

	return _instance;
}
