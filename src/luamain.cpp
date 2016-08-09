#include <lua/lua.hpp>
#include <string.h>
#include <stdio.h>

int l_ink(lua_State *L) {
	int x;
	if (lua_gettop(L) >= 0) {
		x = (int) lua_tonumber(L, -1);
		lua_pushnumber(L, x + 1);
	}
	return 1;
}

int main(int argc, char* argv[]){
	lua_State *l;
	l = lua_open();
	luaL_openlibs(l);
	lua_pushcfunction(l, l_ink);
	lua_setglobal(l, "ink");
	 
	if(luaL_loadfile(l, "test.lua") != 0){
		fprintf(stderr, "lua couldn't parse '%s': %s.\n", "test.lua", lua_tostring(l, -1));
	}else{
		//calls the loaded code
		lua_pcall(l, 0, 1, 0);
		if(lua_isnumber(l, lua_gettop(l)) != 0){
			lua_Integer returnCode = lua_tointeger(l, lua_gettop(l));
			printf("Return code %d\n", (int)returnCode);
		}

		lua_getglobal(l, "add");
		lua_pushnumber(l, 10);
		lua_pushnumber(l, 20);
		if(lua_pcall(l,2,1,0) != 0){
			fprintf(stderr, "Couldn't call add error:\t%s.\n", "test.lua", lua_tostring(l, -1));
		}else{
			int result = (int)lua_tonumber(l, -1);
			printf("Add result of 10 + 20 = %d\n", result);
			//clear the result
			lua_pop(l,1);
		}
		//clears the stack
		lua_pop(l, lua_gettop(l));

	}

	return 0;

}
