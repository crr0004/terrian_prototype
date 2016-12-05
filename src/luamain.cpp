#include <terrian_config.hpp>
#include <lua/lua.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second

int l_ink(lua_State *L) {
	int x;
	if (lua_gettop(L) >= 0) {
		x = (int)lua_tonumber(L, -1);
		lua_pushnumber(L, x + 1);
	}
	return 1;
}

struct Dog
{
	int age;
	int height;
	const char* breed;
};


static int newDog(lua_State* l) {
	Dog* bella = (Dog*)lua_newuserdata(l, sizeof(Dog));
	luaL_getmetatable(l, "Dog");
	    // assert(lua_istable(L, -1)) if you're paranoid
	lua_setmetatable(l, -2);
	srand((unsigned int)time(NULL));
	bella->age = rand() % 100;
	bella->height = 1;

	return 1;
}

static int DogGetAge(lua_State* l) {
	Dog *bella = (Dog*)lua_touserdata(l, 1);
	luaL_argcheck(l, bella != NULL, 1, "Dog expected");
	lua_pushinteger(l, bella->age);
	return 1;
}

static const struct luaL_Reg doglib[] = {
	{"new", newDog},
	{NULL, NULL}

};
static const struct luaL_Reg doglibMember[] = {
	{"age", DogGetAge},
	{NULL, NULL}

};

static void PrintLuaTypeAt(lua_State* l, const int i) {

	int type = lua_type(l, i);
	printf("Stack index %d\t\t", lua_absindex(l, i));
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


static void PrintTableAt(lua_State* l, int index){
	int tableIndex = lua_absindex(l, index);
	if (lua_istable(l, tableIndex) == 1) {
		lua_pushnil(l);               // pushes the first key (which is nil for whatever reason) onto the stack
		while (lua_next(l, tableIndex) != 0) { // key(-1) is replaced by the next key(-1) in table(tableIndex)
			PrintLuaTypeAt(l, -2);
			PrintLuaTypeAt(l, -1);
			lua_pop(l, 1);               // remove value(-1), now key on top at(-1)
			//leaves key(-1) at top for next interation
		}
	}
	else {
		fprintf(stderr, "Object at %d on stack is not a table\n", tableIndex);
	}

}
static void PrintTable(lua_State* l) {
	PrintTableAt(l, -1);
}

//From Programming in Lua 3rd Edition
static void stackDump (lua_State *L) {
	int i;
	int top = lua_gettop(L); /* depth of the stack */
	for (i = 1; i <= top; i++) { /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {
			case LUA_TSTRING: { /* strings */
								  printf("'%s'", lua_tostring(L, i));
								  break;
							  }
			case LUA_TBOOLEAN: { /* booleans */
								   printf(lua_toboolean(L, i) ? "true" : "false");
								   break;
							   }
			case LUA_TNUMBER: { /* numbers */
								  printf("%g", lua_tonumber(L, i));
								  break;
							  }
			default: { /* other values */
						 printf("%s", lua_typename(L, t));
						 break;
					 }
		}
		printf(" "); /* put a separator */
	}
	printf("\n"); /* end the listing */
}

static void PrintGlobalTable(lua_State* l) {
	lua_pushglobaltable(l);
	printf("Global table\n");
	PrintTable(l);
	lua_pop(l, 1);
}

static void CopyTableAtTo(lua_State* l, int t, int newTableIndex){
	t = lua_absindex(l, t);
	newTableIndex = lua_absindex(l, newTableIndex);
	printf("t is %d, newTableIndex is %d\n", t, newTableIndex);
	lua_pushnil(l);
	while(lua_next(l, t) != 0){
		lua_pushvalue(l,-2); //copies key to top so lua_next is happy
		//swaps value and key on top of stack.
		//Above function adds a value onto stack so -2 is now value
		lua_insert(l,-2); 
		//Set the value in the new stack. Consuming the top value and key
		lua_settable(l,newTableIndex);

	}

}

void LuaHook(lua_State *l, lua_Debug *ar) {
	if(lua_getstack(l,0,ar) == 0){
		fprintf(stderr, "%s\n", "Error calling get stack");
	}
	if(lua_getinfo(l, "Snlf", ar) == 0){
		fprintf(stderr, "%s\n", "Error calling get info");
	}else{
		printf("Event %d\tLine %d\t\t",ar->event, ar->currentline);
		if(strcmp(ar->namewhat, "global") == 0){
			printf("Type: %s\tName %s",ar->namewhat,ar->name);
		}
		printf("%s\n","");
	}

}

int main(int argc, char* argv[]) {
	lua_State *l;
	l = luaL_newstate();
	luaL_openlibs(l);
	//PrintGlobalTable(l);
	//Creates a metatable and registers in Lua's registery
	luaL_newmetatable(l, "Dog");
	//Sets functions against the meta table
	luaL_setfuncs(l, doglibMember, 0);
	//Adds __index 	to the meta table so we can use functions against
	/*
	 * Lua uses : syntax which causes an index lookup
	 * It uses the following function name to look in the meta table
	 * By adding __index we ensure that it always looks at its self
	 *
	 * I.E __index becomes the metatable itself which contains our functions
	*/
	lua_setfield(l, -1, "__index");
	luaL_getmetatable(l, "Dog");
	luaL_newlib(l, doglib);
	lua_setglobal(l, "dog");

	lua_Debug ar;

	lua_newtable(l);
	lua_pushglobaltable(l);
	int globalTableIndex = lua_absindex(l,-2);
	CopyTableAtTo(l, -1, -2);

	//lua_sethook(l, LuaHook, LUA_MASKLINE | LUA_MASKCALL | LUA_MASKRET, 0);
//	lua_sethook(l, LuaHook, LUA_MASKLINE | LUA_MASKCALL, 0);
	if (luaL_loadfile(l, concat(xstr(SCRIPTS_DIR), "/test.lua")) != 0) {
		fprintf(stderr, "lua couldn't parse '%s': %s.\n", "test.lua", lua_tostring(l, -1));
	}
	else {
		lua_pcall(l, 0, 0, 0);
		lua_getglobal(l, "update");
		if (lua_pcall(l, 0, 0, 0) != 0) {
			fprintf(stderr, "lua couldn't call update in '%s': %s.\n", "test.lua", lua_tostring(l, -1));
		}
	}

	int i = 0;
	char in = 'e';//(char)getchar();

	while (in != 'e') {

		for (i = 0; i < 1; i++) {

			int indexStart = lua_gettop(l);
			//lua_rawseti(l, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
			if (luaL_loadfile(l, concat(xstr(SCRIPTS_DIR), "/test.lua")) != 0) {
				fprintf(stderr, "lua couldn't parse '%s': %s.\n", "test.lua", lua_tostring(l, -1));
			}
			else {
				PrintTableAt(l, globalTableIndex);
				lua_pcall(l, 0, 0, 0);
				lua_getglobal(l, "update");
				if (lua_pcall(l, 0, 0, 0) != 0) {
					fprintf(stderr, "lua couldn't call update in '%s': %s.\n", "test.lua", lua_tostring(l, -1));
				}
				lua_getglobal(l, "createDog");
				if (lua_pcall(l, 0, 0, 0) != 0) {
					fprintf(stderr, "lua couldn't call createDog in '%s': %s.\n", "test.lua", lua_tostring(l, -1));
				}
				lua_pop(l, lua_gettop(l) - indexStart);
			}
			/*
			if (luaL_loadfile(l, concat(xstr(SCRIPTS_DIR), "/hello.lua")) != 0) {
				fprintf(stderr, "lua couldn't parse '%s': %s.\n", "hello.lua", lua_tostring(l, -1));
			}
			else {
				lua_pcall(l, 0, 0, 0);
				lua_getglobal(l, "update");
				if (lua_pcall(l, 0, 0, 0) != 0) {
					fprintf(stderr, "lua couldn't call update in '%s': %s.\n", "hello.lua", lua_tostring(l, -1));
				}
				lua_pop(l, lua_gettop(l));
			}
			//PrintGlobalTable(l);
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
				fprintf(stderr, "Couldn't call add error:\t%s\n", lua_tostring(l, -1));
			}else{
				int result = (int)lua_tonumber(l, -1);
				printf("Add result of 10 + 20 = %d\n", result);
				//clear the result
				lua_pop(l,1);
			}
			lua_getglobal(l, "createDog");
			if (lua_pcall(l, 0, 0, 0) != 0) {
				fprintf(stderr, "Couldn't call function error:\t%s\n", lua_tostring(l, -1));
			}
			*/

		}
		in = (char)getchar();
	}
	return 0;
}
