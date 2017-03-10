#include "triangle.hpp"
#include <fmt/format.h>
#include <glm/glm.hpp>
#include "addtodrawqueue.hpp"
#include "luae/scriptriangle.hpp"
#include "luae/scriptmanager.hpp"
#include "luae/Utilities.hpp"
using namespace Luae;

static const struct luaL_Reg LuaFunctions[] = {
	{"Create", ScriptTriangle::Create},
	{NULL, NULL}

};
static const struct luaL_Reg LuaMembers[] = {
	{"getVertices", ScriptTriangle::GetTriangleVerticesAsTable},
	{"translate", ScriptTriangle::Translate},
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
	//triangle->translate(glm::vec3(5.0,0.0,0.0));


	return 1;
}
int ScriptTriangle::Translate(lua_State* l){
	Triangle* triangle = *(Triangle**)lua_touserdata(l,-2);
	float x = luae_float_getfield(l,-1,1);
	float y = luae_float_getfield(l,-1,2);
	float z = luae_float_getfield(l,-1,3);
	fmt::printf("X: %f, Y: %f, Z: %f\n", x, y, z);
	triangle->translate(glm::vec3(x,y,z));

	return 0;

}

int ScriptTriangle::Create(lua_State* l){
	Triangle** triangle = (Triangle **)lua_newuserdata(l, sizeof(Triangle*));
	*triangle = new Triangle;
	luaL_getmetatable(l, "TriangleMetatable");
	lua_setmetatable(l, -2);
	(*triangle)->buildStatic();
	(*triangle)->setShaderLocations("vert");
	AddToDrawQueueCommand addTriangle(*triangle);
	addTriangle.execute();

	//Amount of variables to return
	return 1;
}
