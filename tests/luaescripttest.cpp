#include <catch.hpp>
#include <string>
#include <cstring>
#include <lua/lua.hpp>
#include "luae/scriptmanager.hpp"
#include "luae/script.hpp"
#include "luae/Utilities.hpp"

TEST_CASE("Load script"){
	Luae::ScriptManager::instance();

	SECTION("Load named script"){
		
		Luae::Script* script = Luae::Script::Load("update.lua");

		REQUIRE(script != NULL);
		INFO("Script name is " << script->getScriptName());
		int result = std::strcmp(script->getScriptName(), "update.lua");

		REQUIRE(result == 0);

		delete script;
	}

	SECTION("Failed load script"){
		Luae::Script* script = Luae::Script::Load(std::string("doesnt_exist.lua"));
		REQUIRE(script == NULL);
	}
	SECTION("Load script from string"){
		const char* source =
			"function update()\n"
			"--print(\"update called\")\n"
			"end";		
		Luae::Script* script = Luae::Script::Load("test", source);
		REQUIRE(script != NULL);
	}
	Luae::ScriptManager::Close();

}

TEST_CASE("Call functions"){

	SECTION("Has named function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		bool result = script->has("update");
		REQUIRE(result);

		delete script;
	}
	SECTION("Failed has named function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		bool result = script->has("nofunction");
		REQUIRE(!result);

		delete script;
	}
	SECTION("Call named function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		bool result = script->call("update");

		REQUIRE(result);

		delete script;
	}
	SECTION("Fail called name function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		bool result = script->call("uupdate");
		REQUIRE(!result);
		delete script;
	}
	Luae::ScriptManager::Close();
}


TEST_CASE("Pop and push lua state"){
	const char* source =
		"hello = 2\n"
		"--header = {\n"
		"--functions = {update=update, update2=update2},\n"
		"--variables = {test}\n"
		"--}\n"
		"";
	const char* source2 =
		"hello = 1\n"
		"";

	lua_State* lua = Luae::ScriptManager::instance()->getState();
	Luae::Script* script = Luae::Script::Load("Pop lua state", source);
	REQUIRE(script != NULL);
	Luae::Script* script2 = Luae::Script::Load("Second script", source2);
	//Should restore hello as 2
	script->push();
	lua_getglobal(lua, "hello");
	int hello = (int)lua_tonumber(lua, -1);
	REQUIRE(hello == 2);
	script->pop();
	script2->push();

	lua_getglobal(lua, "hello");
	hello = (int)lua_tonumber(lua, -1);
	REQUIRE(hello == 1);
	lua_pop(lua,2);
	Luae::ScriptManager::Close();
}
