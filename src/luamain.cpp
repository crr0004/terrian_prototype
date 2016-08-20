#include <terrian_config.h>
#include <lua/lua.hpp>
#include <string.h>
#include <stdio.h>

//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second

int l_ink(lua_State *L) {
	int x;
	if (lua_gettop(L) >= 0) {
		x = (int) lua_tonumber(L, -1);
		lua_pushnumber(L, x + 1);
	}
	return 1;
}

struct Dog
{
	int age = 0;
	int height = 0;
	const char* breed;
};


static int newDog(lua_State* l) {
	Dog* bella = (Dog*)lua_newuserdata(l, sizeof(Dog));
	bella->age = 12;
	bella->height = 1;

	return 1;
}

static int DogGetAge(lua_State* l) {
	Dog *bella = (Dog*)lua_touserdata(l, 1);
	luaL_argcheck(l, bella != NULL, 1, "Dog expected");
	lua_pushinteger(l, bella->age);
	return 1;
}

static const struct luaL_reg doglib[] = {
	{"new", newDog},
	{"age", DogGetAge},
	{NULL, NULL}

};

static void PrintLuaTypeAt(lua_State* l, const int i) {

	int type = lua_type(l, i);
	switch (type) {

	case LUA_TNIL:
		break;
	case LUA_TBOOLEAN:
		printf("Value is boolean: %d\n", (int)lua_toboolean(l, i));
		break;
	case LUA_TLIGHTUSERDATA:
		printf("Value is light user data (just a pointer)\n");
		break;
	case LUA_TNUMBER:
		printf("Value is a number of: %d\n", (int)lua_tonumber(l, i));
		break;
	case LUA_TSTRING:
		printf("Value is a string of: %s\n", lua_tostring(l, i));
		break;
	case LUA_TTABLE:
		printf("Value is a table.\n");
		break;
	case LUA_TFUNCTION:
		printf("Value is a function.\n");
		break;
	case LUA_TUSERDATA:
		printf("Value is userdata\n");
		break;
	default:
		printf("Value is not printable\n");
		break;
	}
}


int main(int argc, char* argv[]){
	lua_State *l;
	l = lua_open();
	luaL_openlibs(l);
	luaL_openlib(l, "dog", doglib, 0);
	int stackTop = 0;
	int i = 0;
	luaL_loadfile(l, concat(xstr(SCRIPTS_DIR), "/test.luac"));
	lua_pcall(l, 0, 0, 0);
	char in = (char)getchar();

	lua_rawgeti(l, LUA_REGISTRYINDEX, LUA_GLOBALSINDEX);
	PrintLuaTypeAt(l, -1);
	//lua_pushnil(l);               // put a nil key on stack
	while (lua_next(l, -2) != 0) { // key(-1) is replaced by the next key(-1) in table(-2)
		PrintLuaTypeAt(l, -2);
		lua_pop(l, 1);               // remove value(-1), now key on top at(-1)
	}
	lua_pop(l, 1);                 // remove global table(-1)
	while (in != 'e') {

			stackTop = lua_gettop(l);
		for (i = 0; i < 1000; i++) {

			if (luaL_loadfile(l, concat(xstr(SCRIPTS_DIR), "/test.luac")) != 0) {
				fprintf(stderr, "lua couldn't parse '%s': %s.\n", "test.lua", lua_tostring(l, -1));
			}
				lua_pcall(l, 0, 0, 0);
				//calls the loaded code
				/*
				lua_pcall(l, 0, 1, 0);
				if(lua_isnumber(l, lua_gettop(l)) != 0){
					lua_Integer returnCode = lua_tointeger(l, lua_gettop(l));
					printf("Return code %d\n", (int)returnCode);
				}
				lua_getglobal(l, "add");
				lua_pushnumber(l, 10);
				lua_pushnumber(l, 20);
				if(lua_pcall(l,2,1,0) != 0){
					fprintf(stderr, "Couldn't call add error:\t%s\n", lua_tostring(l, -1));
				}else{
					int result = (int)lua_tonumber(l, -1);
					printf("Add result of 10 + 20 = %d\n", result);
					//clear the result
					lua_pop(l,1);
				}
				*/

				lua_getglobal(l, "createDog");
				if (lua_pcall(l, 0, 0, 0) != 0) {
					fprintf(stderr, "Couldn't call function error:\t%s\n", lua_tostring(l, -1));
				}
		}
			printf("Stack size: %d\n", lua_gettop(l));
			//printf("Popping %d elements from lua stack\n", lua_gettop(l) - stackTop);
			//lua_pop(l, lua_gettop(l) - stackTop);
		in = (char)getchar();
	}
	int ch = getchar();
	return 0;
}
