#include "heightmap.h"
#include <GLFW/glfw3.h>
#include "logiccontext.h"
using namespace HeightmapName;

Heightmap::Heightmap(){

}

void Heightmap::draw(LogicContext* state){
	polygon.draw(state);

}

void Heightmap::update(LogicContext* state){
	polygon.update(state);

}

void Heightmap::setShaderLocations(GLuint vertShaderLocation){

	polygon.setShaderLocations(vertShaderLocation);
}

void Heightmap::build(HeightmapSettings settings){
	int squareCount = 3;//settings.widthDensity*settings.widthDensity;
	//@TODO: these should be allocated outside here
	GLfloat vertices[3*4*squareCount]; //3 is elements. 4 is for square
	GLuint indices[2*3*squareCount];//2 triangles per square, 3 indices per triangle

	//this should be calculated from the map origin and the map extents
	glm::vec3 squareOrigin = settings.origin;//glm::vec3(0.0f, 0.0f, 0.0f);
	//Vector to move right
	glm::vec3 moveRight = glm::vec3(1.0f, 0.0f, 0.0f);
	//Vector to move down
	glm::vec3 moveDown = glm::vec3(0.0f, 0.0f, 1.0f);

	//Generate first square outside loop	
	//move into a general function
	vertices[0] = squareOrigin[0];
	vertices[1] = squareOrigin[1];
	vertices[2] = squareOrigin[2];

	vertices[3] = squareOrigin[0] + 1.0f;
	vertices[4] = squareOrigin[1] + 0.0f;
	vertices[5] = squareOrigin[2] + 0.0f;

	vertices[6] = squareOrigin[0] + 1.0f;
	vertices[7] = squareOrigin[1] + 0.0f;
	vertices[8] = squareOrigin[2] + 1.0f;

	vertices[9] = squareOrigin[0] + 0.0f;
	vertices[10] = squareOrigin[1] + 0.0f;
	vertices[11] = squareOrigin[2] + 1.0f;

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
	squareOrigin = squareOrigin + moveRight;

	vertices[12] = squareOrigin[0] + 1.0f;
	vertices[13] = squareOrigin[1] + 0.0f;
	vertices[14] = squareOrigin[2] + 0.0f;

	vertices[15] = squareOrigin[0] + 1.0f;
	vertices[16] = squareOrigin[1] + 0.0f;
	vertices[17] = squareOrigin[2] + 1.0f;

	indices[6] = 1;
	indices[7] = 4;
	indices[8] = 5;
	indices[9] = 5;
	indices[10] = 2;
	indices[11] = 1;
	squareOrigin = squareOrigin + moveRight;

	vertices[18] = squareOrigin[0] + 1.0f;
	vertices[19] = squareOrigin[1] + 0.0f;
	vertices[20] = squareOrigin[2] + 0.0f;

	vertices[21] = squareOrigin[0] + 1.0f;
	vertices[22] = squareOrigin[1] + 0.0f;
	vertices[23] = squareOrigin[2] + 1.0f;

	indices[12] = 4;
	indices[13] = 6;
	indices[14] = 7;
	indices[15] = 7;
	indices[16] = 5;
	indices[17] = 4;

	/*
	for(int i = 1; i < squareCount*2; i++){
		//Square is in top row
		if(i < settings.widthDensity){

		}else{

		}
		//Internal squares (surronded on each side)
		//Shared vertices: bottom left, top right, top left
		//New: bottom right

		//First row squares
		//Shared vertices: bottom left, top left
		//New: bottom right, top right

		//First square in row. I.E first column
		//Shared vertices: Top left, top right
		//New vertices: Bottom left, bottom right

	}
	*/
	polygon.setVertices(vertices, sizeof(vertices) / sizeof(GLfloat));
	polygon.setIndices(indices, sizeof(indices) / sizeof(GLuint));
	polygon.buildStatic();
	polygon.rotate(glm::vec3(-1.0f,0.0f,0.0f), 1.57f);

}
