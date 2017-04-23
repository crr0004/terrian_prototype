#include "luae/scriptcollision.hpp"
#include "luae/scriptmanager.hpp"

using namespace Luae;
static const struct luaL_Reg LuaFunctions[] = {
	{"GetPointFromRay", ScriptCollision::GetPointFromRay},
	{NULL, NULL}

};
static const struct luaL_Reg LuaMembers[] = {
	{NULL, NULL}
};

void ScriptCollision::AddToLib(){
	ScriptManager::instance()->NewLib(LuaFunctions, "ScriptCollision");
}

int ScriptCollision::GetPointFromRay(lua_State* l){

	return 0;
}
