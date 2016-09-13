#include "luae/scriptmanager.h"
#include <lua/lua.hpp>
#include "terrian_config.h"

//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second

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
void ScriptManager::NewLib(const struct luaL_Reg lib[], const char* name) {
	luaL_newlib(state, lib);
	lua_setglobal(state, name);
}

void ScriptManager::LoadScript(const char* name) {
	if (luaL_loadfile(l, concat(xstr(SCRIPTS_DIR), name)) != 0) {
		fprintf(stderr, "lua couldn't parse '%s': %s.\n", "test.lua", lua_tostring(l, -1));
	}
			
}

ScriptManager* ScriptManager::instance(){
	if(ScriptManager::_instance == 0){
		_instance = new ScriptManager();
	}

	return _instance;

}
