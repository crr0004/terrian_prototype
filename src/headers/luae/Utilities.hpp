#ifndef LUAE_UTILITIES_H
#define LUAE_UTILITIES_H
#include <lua/lua.hpp>
#include <stdio.h>

namespace Luae{

	//TODO Rename so luae_ is prefixed
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

	//TODO Rename so luae_ is prefixed
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
	//TODO Rename so luae_ is prefixed
	static void PrintTable(lua_State* l) {
		PrintTableAt(l, -1);
	}

	//From Programming in Lua 3rd Edition
	//TODO Rename so luae_ is prefixed
	static void stackDump (lua_State *L) {
		int i;
		int top = lua_gettop(L); /* depth of the stack */
		for (i = top; i >= 1; i--) { /* repeat for each level */
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

	//TODO Rename so luae_ is prefixed
	static void PrintGlobalTable(lua_State* l) {
		lua_pushglobaltable(l);
		printf("Global table\n");
		PrintTable(l);
		lua_pop(l, 1);
	}

	//TODO Rename so luae_ is prefixed
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
	static int luae_int_getfield(lua_State* l, int pos, const char* name){
		lua_getfield(l, pos, name);
		int value = lua_tonumber(l,pos);
		lua_pop(l,1);
		return value;
	}
	static float luae_float_getfield(lua_State* l, int pos, const char* name){
		lua_getfield(l, pos, name);
		float value = lua_tonumber(l,pos);
		lua_pop(l,1);
		return value;
	}
	static float luae_float_getfield(lua_State* l, int pos, int index){
		lua_rawgeti(l, pos, index);
		float value = lua_tonumber(l,pos);
		lua_pop(l,1);
		return value;
	}
}

#endif // !LUAE_UTILITIES_H

