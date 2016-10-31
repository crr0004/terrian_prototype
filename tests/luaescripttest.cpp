#include <catch.hpp>
#include <string>
#include <cstring>
#include "luae/script.hpp"

TEST_CASE("Load script"){
	SECTION("Load named script"){
		Luae::Script* script = Luae::Script::Load(std::string("update.lua"));
		REQUIRE(script != NULL);
		REQUIRE(std::strcmp(script->getScriptName(), "update.lua") == 0);

		delete script;


	}
	SECTION("Failed load script"){
		Luae::Script* script = Luae::Script::Load(std::string("doesnt_exist.lua"));
		REQUIRE(script == NULL);
	}

}

TEST_CASE("Call functions"){

	SECTION("Has named function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		REQUIRE(script->has("update"));

		delete script;
	}
	SECTION("Failed has named function"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		REQUIRE(!script->has("nofunction"));

		delete script;
	}
	SECTION("Call named function"){

	}
	SECTION("Faile called name function"){


	}


}
