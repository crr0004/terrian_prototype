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
	{"v1", ScriptTriangle::SetVert1},
	{"v2", ScriptTriangle::SetVert2},
	{"v3", ScriptTriangle::SetVert3},
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

int ScriptTriangle::SetVert1(lua_State* l){
	Triangle* triangle = *(Triangle**)lua_touserdata(l,-2);
	float x = luae_float_getfield(l,-1,1);
	float y = luae_float_getfield(l,-1,2);
	float z = luae_float_getfield(l,-1,3);
	GLfloat* vertices = triangle->getVertices();
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = z;
}
int ScriptTriangle::SetVert2(lua_State* l){
	Triangle* triangle = *(Triangle**)lua_touserdata(l,-2);
	float x = luae_float_getfield(l,-1,1);
	float y = luae_float_getfield(l,-1,2);
	float z = luae_float_getfield(l,-1,3);
	GLfloat* vertices = triangle->getVertices();
	vertices[3] = x;
	vertices[4] = y;
	vertices[5] = z;

}
int ScriptTriangle::SetVert3(lua_State* l){
	int stackCount = lua_gettop(l);
	int returnCount = 0;
	Triangle* triangle = *(Triangle**)lua_touserdata(l,-stackCount);
	GLfloat* vertices = triangle->getVertices();

	if(stackCount >= 2){	
		float x = luae_float_getfield(l,-1,1);
		float y = luae_float_getfield(l,-1,2);
		float z = luae_float_getfield(l,-1,3);
		vertices[6] = x;
		vertices[7] = y;
		vertices[8] = z;
	}else if(stackCount == 1){
		lua_createtable(l, 0, 3);
		lua_pushnumber(l, vertices[6]);
		lua_rawseti(l, -2, 1);
		lua_pushnumber(l, vertices[7]);
		lua_rawseti(l, -2, 2);
		lua_pushnumber(l, vertices[8]);
		lua_rawseti(l, -2, 3);
		returnCount = 1;

	}
	fmt::printf("Stack count: %d\n", lua_gettop(l));

	return returnCount;

}
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
