#include <fmt/format.h>
#include <glm/glm.hpp>
#include "luae/scriptriangle.hpp"
#include "luae/scriptmanager.hpp"
#include "luae/Utilities.hpp"
#include "triangle.hpp"
using namespace Luae;

static const struct luaL_Reg LuaFunctions[] = {
	{"Create", ScriptTriangle::Create},
	{NULL, NULL}

};
static const struct luaL_Reg LuaMembers[] = {
	{"getVertices", ScriptTriangle::GetTriangleVerticesAsTable},
	{NULL, NULL}
};

void ScriptTriangle::AddToLib(){
	ScriptManager::instance()->NewLib(LuaFunctions, "Triangle");
	ScriptManager::instance()->NewMetaLib(LuaMembers, "TriangleMetatable");
}

/*
int ScriptTriangle::GetSettings(lua_State* l){
	lua_getglobal(l,"HeightmapObject");
	lua_pop(l,1);

	return 0;
}
*/

int ScriptTriangle::GetTriangleVerticesAsTable(lua_State* l){
	Triangle* triangle = *(Triangle**)lua_touserdata(l,-1);
	GLfloat* vertices = triangle->getVertices();

	lua_createtable(l, 0, 9);
	for(int i = 1; i <= triangle->getVertexSize(); i++){
		lua_pushnumber(l, vertices[i-1]);
		lua_rawseti(l, -2, i);
	}


	return 1;
}

int ScriptTriangle::Create(lua_State* l){
	Triangle** triangle = (Triangle **)lua_newuserdata(l, sizeof(Triangle*));
	*triangle = new Triangle;
	luaL_getmetatable(l, "TriangleMetatable");
	lua_setmetatable(l, -2);
	(*triangle)->buildStatic();
	(*triangle)->setShaderLocations("vert");

	//Amount of variables to return
	return 1;
}
