#include <catch.hpp>
#include <string>
#include <cstring>
#include <fmt/format.h>
#include "luae/script.hpp"
#include "luae/scriptmanager.hpp"


class ScriptManagerMockClass{
	public:
		static	void noParams();
		static void withParam(const char* printMe);
		static const char* withReturn();
		static const char* withTableReturn();
		static int luaeNoParams(lua_State* l);
		static int luaeWithParam(lua_State* l);
		static int luaeWithReturn(lua_State* l);
		static int luaeWithTableReturn(lua_State* l);
		static bool lastFunctionWorked;


};
bool ScriptManagerMockClass::lastFunctionWorked = false;
int ScriptManagerMockClass::luaeNoParams(lua_State* l){
	ScriptManagerMockClass::noParams();

	return 0;

}
int ScriptManagerMockClass::luaeWithParam(lua_State* l){

	return 0;

}
int ScriptManagerMockClass::luaeWithReturn(lua_State* l){

	return 0;

}
int ScriptManagerMockClass::luaeWithTableReturn(lua_State* l){


	return 0;
}

void ScriptManagerMockClass::noParams(){
	ScriptManagerMockClass::lastFunctionWorked = true;
	fmt::print("noParams\n");
}

static const struct luaL_Reg MockClass[] = {
	{"noParams", ScriptManagerMockClass::luaeNoParams},
	{"withReturn", ScriptManagerMockClass::luaeWithReturn},
	{"withParams", ScriptManagerMockClass::luaeWithParam},
	{"withTableReturn", ScriptManagerMockClass::luaeWithTableReturn},
	{NULL, NULL}

};

TEST_CASE("ScriptManager Lib Tests"){


	ScriptManager::instance()->NewLib(MockClass, "MockClass");
	ScriptManagerMockClass::lastFunctionWorked = false;


	SECTION("Add lib"){
		ScriptManager::instance()->NewLib(MockClass, "MockClass");

	}
	SECTION("Call lib function"){

		Luae::Script* script = Luae::Script::Load("scriptmanagertests.lua");

		bool result = script->has("callLib");
		REQUIRE(result);

		bool callResult = script->call("callLib");
		REQUIRE(callResult);
		REQUIRE(ScriptManagerMockClass::lastFunctionWorked);

		delete script;

	}
	SECTION("Call lib function with paramters"){
		Luae::Script* script = Luae::Script::Load("scriptmanagertests.lua");
		bool result = script->has("callLibParams");
		REQUIRE(result);
		delete script;

	}
	SECTION("Call lib function with return value"){
		Luae::Script* script = Luae::Script::Load("scriptmanagertests.lua");
		bool result = script->has("callLibReturn");
		REQUIRE(result);
		delete script;

	}
	SECTION("Call lib function with table return"){
		Luae::Script* script = Luae::Script::Load("scriptmanagertests.lua");
		bool result = script->has("callLibTableReturn");
		REQUIRE(result);
		delete script;

	}
	/*
	 * TODO: Figure out what I am doing here
	 SECTION("Lib debug information"){

	 REQUIRE(script->has("callLib"));

	 }
	 */

}

