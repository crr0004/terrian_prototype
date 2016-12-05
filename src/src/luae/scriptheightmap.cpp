#include <fmt/format.h>
#include <glm/glm.hpp>
#include "luae/scriptheightmap.hpp"
#include "luae/scriptmanager.hpp"
#include "luae/Utilities.hpp"
#include "heightmap.hpp"
using namespace Luae;

/*
Public functions to possibly expose to scripts
			Heightmap(GLfloat* vertices, GLuint* indices);
			Heightmap(HeightmapSettings settings);
Start here
			void build(HeightmapSettings settings);
			void draw(LogicContext* state);
			void update(LogicContext* state);
			void setShaderLocations(GLuint vertShaderLocation);
			int getIndexOfSquareIntersectingLine(glm::vec3 a, glm::vec3 b);
			int getIndexOfSquare(int squareNumber);
			int getIndexOfSquareVertex(int squareNumber, int vertexNumber);
			void rotate(glm::vec3 rotateAround, float rotateBy);
*/
static const struct luaL_Reg LuaFunctions[] = {
	{"Build", ScriptHeightMap::Build},
	{NULL, NULL}

};
static const struct luaL_Reg LuaMembers[] = {
	{"getSettings", ScriptHeightMap::GetSettings},
	{NULL, NULL}

};

void ScriptHeightMap::AddToLib(){
	ScriptManager::instance()->NewLib(LuaFunctions, "Heightmap");
	ScriptManager::instance()->NewMetaLib(LuaMembers, "HeightmapMetatable");
}

int ScriptHeightMap::GetSettings(lua_State* l){
	lua_getglobal(l,"HeightmapObject");
	lua_pop(l,1);

	return 0;
}

int ScriptHeightMap::Build(lua_State* l){
	int width = luae_int_getfield(l,-1,"width");
	int widthDensity = luae_int_getfield(l, -1, "widthDensity");
	float x = luae_float_getfield(l, -1, "x");
	float y = luae_float_getfield(l, -1, "y");
	float z = luae_float_getfield(l, -1, "z");

	HeightmapSettings *settingsToPass = new HeightmapSettings;
	settingsToPass->width = width;
	settingsToPass->widthDensity = widthDensity;
	settingsToPass->origin = glm::vec3(x, y, z);
	//((Heightmap*)lua_newuserdata(l, sizeof(Heightmap*))) = heightmapNew;
	Heightmap** heightmapPointer = (Heightmap **)lua_newuserdata(l, sizeof(Heightmap*));
	*heightmapPointer = new Heightmap(settingsToPass);
	luaL_getmetatable(l, "HeightmapMetatable");
	lua_setmetatable(l, -2);
	//(*heightmapPointer)->build(settingsToPass);

	/*
	HeightmapSettings heightmapSettings;

	heightmapSettings.widthDensity = 10;
	heightmapSettings.origin = glm::vec3(0.0f, 0.0f, 0.0f);

	Heightmap heightmap(heightmapSettings);
	heightmap.build(heightmapSettings);
	//heightmap.setShaderLocations(vertShaderLocation);
	heightmap.rotate(glm::vec3(1,0,0), -1.57f);
	*/ 
	return 1;
}
