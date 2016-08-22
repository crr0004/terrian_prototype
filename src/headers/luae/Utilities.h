#ifndef LUAE_UTILITIES_H
#define LUAE_UTILITIES_H
#include <lua/lua.hpp>
#include <stdio.h>
namespace LuaE {

static void PrintLuaTypeAt(lua_State* l, const int i) {

	int type = lua_type(l, i);
	printf("Stack index %d\t\t", i);
	switch (type) {

	case LUA_TNIL:
		printf("Value is nil.\n");
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

static void PrintTable(lua_State* l) {
	if (lua_istable(l, -1) == 1) {
		lua_pushnil(l);               // pushes the first key (which is nil for whatever reason) onto the stack
		while (lua_next(l, -2) != 0) { // key(-1) is replaced by the next key(-1) in table(-2)
			PrintLuaTypeAt(l, -2);
			PrintLuaTypeAt(l, -1);
			lua_pop(l, 1);               // remove value(-1), now key on top at(-1)
		}
	}
	else {
		fprintf(stderr, "Object on top of stack is not a table\n");
	}
}

static void PrintGlobalTable(lua_State* l) {
	lua_pushglobaltable(l);
	PrintTable(l);
	lua_pop(l, 1);
}
}

#endif // !LUAE_UTILITIES_H

