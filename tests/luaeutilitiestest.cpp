#include <catch.hpp>
#include <lua/lua.hpp>
#include "luae/Utilities.hpp"
#include "luae/scriptmanager.hpp"

TEST_CASE("Lua util tests"){
	using namespace Luae;
	lua_State* l = ScriptManager::instance()->getState();
	SECTION("Copy table"){
		lua_createtable(l, 1, 0);
		lua_createtable(l, 1, 0);
		int FIRST_TABLE = lua_absindex(l, -1);
		int SECOND_TABLE = lua_absindex(l, -2);
		const char* key = "hello";

		lua_pushstring(l, key);
		lua_pushnumber(l, 1);
		lua_settable(l, FIRST_TABLE);

		lua_pushstring(l, key);
		lua_pushnumber(l, 2);
		lua_settable(l, SECOND_TABLE);

		//Can I copy the values from table 1 to table 2
		//change values in table 1 and have the changes not reflected in 2
		//PrintTableAt(l, -1);
		//PrintTableAt(l, -2);

		luae_copytable(l, FIRST_TABLE, SECOND_TABLE);

		lua_pushstring(l, key);
		lua_pushnumber(l, 7);
		lua_settable(l, FIRST_TABLE);

		lua_pushstring(l, key);
		lua_gettable(l, SECOND_TABLE);
		int hello_value = (int)lua_tonumber(l, -1);
		REQUIRE(hello_value == 1);
	}

	Luae::ScriptManager::Close();
}

