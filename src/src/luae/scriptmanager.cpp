#include "luae/scriptmanager.hpp"
#include <lua/lua.hpp>
#include <fmt/format.h>

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
	/*
	int nup = 0;
	fmt::printf("Table count %d\n", sizeof(lib)/sizeof((lib)[0]) -1);
	lua_createtable(state, 0, sizeof(lib)/sizeof((lib)[0]) -1);
	luaL_checkversion(state);
	luaL_checkstack(state, nup, "too many upvalues");
	for (; lib->name != NULL; lib++) {  // fill the table with given functions
		int i;
		for (i = 0; i < nup; i++)  // copy upvalues to the top
			lua_pushvalue(state, -nup);
		lua_pushcclosure(state, lib->func, nup);  // closure with those upvalues
		lua_setfield(state, -(nup + 2), lib->name);
	}
	lua_pop(state, nup);  // remove upvalues
	*/
	luaL_newmetatable(state, name);
	lua_pushstring(state, "hello");
	luaL_setfuncs(state, lib, 1);
	lua_setfield(state, -1, "__index");
}
void ScriptManager::NewLib(const struct luaL_Reg lib[], const char* name) {
	luaL_newlibtable(state,lib);
	luaL_newlib(state, lib);
	lua_setglobal(state, name);
}


ScriptManager* ScriptManager::instance(){
	if(ScriptManager::_instance == 0){
		_instance = new ScriptManager();
	}

	return _instance;
}
