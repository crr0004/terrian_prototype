#include <catch.hpp>
#include "luae/script.hpp"

TEST_CASE("Load script"){
	SECTION("Load named script"){
		Luae::Script* script = Luae::Script::Load("update.lua");
		REQUIRE(script != NULL);

	}
	SECTION("Failed load script"){
		Luae::Script* script = Luae::Script::Load("doesnt_exist.lua");
		REQUIRE(script == NULL);
	}

}

TEST_CASE("Call functions"){

	SECTION("Has named function"){

	}
	SECTION("Failed has named function"){

	}
	SECTION("Call named function"){

	}
	SECTION("Faile called name function"){

	}

}
