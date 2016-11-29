#include <lua/lua.hpp>
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

void ScriptHeightMap::AddToLib(){
	ScriptManager::instance()->NewLib(LuaFunctions, "Heightmap");

}

int ScriptHeightMap::Build(lua_State* l){
	PrintTable(l);
	

	/*
	HeightmapSettings heightmapSettings;

	heightmapSettings.widthDensity = 10;
	heightmapSettings.origin = glm::vec3(0.0f, 0.0f, 0.0f);

	Heightmap heightmap(heightmapSettings);
	heightmap.build(heightmapSettings);
	//heightmap.setShaderLocations(vertShaderLocation);
	heightmap.rotate(glm::vec3(1,0,0), -1.57f);
	*/
	return 0;
}
