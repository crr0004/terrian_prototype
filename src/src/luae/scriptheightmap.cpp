#include <lua/lua.hpp>
#include "luae/scriptheightmap.hpp"
#include "heightmap.hpp"
using namespace Terrian_Prototype;
using namespace Luae;

ScriptHeightMap* ScriptHeightMap::_instance = 0;

ScriptHeightMap* ScriptHeightMap::instance() {
	if (_instance == 0) {
		_instance = new ScriptHeightMap;
	}
	return _instance;
}
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

static int build(lua_State* l){

	HeightmapSettings heightmapSettings;

	heightmapSettings.widthDensity = 10;
	heightmapSettings.origin = glm::vec3(0.0f, 0.0f, 0.0f);

	Heightmap heightmap(heightmapSettings);
	heightmap.build(heightmapSettings);
	//heightmap.setShaderLocations(vertShaderLocation);
	heightmap.rotate(glm::vec3(1,0,0), -1.57f);
	return 0;
}

ScriptHeightMap::ScriptHeightMap() {

}

ScriptHeightMap::~ScriptHeightMap() {
	delete _instance;
	_instance = 0;
}
