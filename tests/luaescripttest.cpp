#include <catch.hpp>
#include <string>
#include <cstring>
#include "luae/script.hpp"

TEST_CASE("Load script"){
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
		delete script;
	}

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

	}
	SECTION("Fail called name function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		bool result = script->call("uupdate");
		REQUIRE(!result);
	}
}
