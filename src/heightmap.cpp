#include "heightmap.h"
#include <GLFW/glfw3.h>
#include "logiccontext.h"
#include <stdio.h>
using namespace HeightmapName;

Heightmap::Heightmap(){}

Heightmap::Heightmap(HeightmapSettings settings){
	squareCount = settings.widthDensity*settings.widthDensity;
	//@TODO: these should be allocated outside here
	vertices = new GLfloat[3*4*squareCount]; //3 is elements. 4 is for square
	indices = new GLuint[2*3*squareCount];//2 triangles per square, 3 indices per triangle

}

Heightmap::~Heightmap(){
	delete vertices;
	delete indices;
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

void Heightmap::addVertex(float vertex){
	vertices[verticesPosition] = vertex;
	verticesPosition++;
}

void Heightmap::addVertex(float v1, float v2, float v3){
	printf("Adding %f %f %f vertices\n", v1, v2, v3);
	addVertex(v1);
	addVertex(v2);
	addVertex(v3);
}

void Heightmap::addIndex(unsigned int index){
	printf("Adding %d index\n", index);
	indices[indicesPosition] = index;
	indicesPosition++;
}

struct PreviousSquare{
	int bottomLeftIndex;
	int bottomRightIndex;
	int topRightIndex;
	int topLeftIndex;
};
void Heightmap::build(HeightmapSettings settings){

	//this should be calculated from the map origin and the map extents
	glm::vec3 squareOrigin = glm::vec3(settings.origin);//glm::vec3(0.0f, 0.0f, 0.0f);
	//Vector to move right
	glm::vec3 moveRight = glm::vec3(1.0f, 0.0f, 0.0f);
	//Vector to move down
	glm::vec3 moveDown = glm::vec3(0.0f, 0.0f, -1.0f);

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

	//Variables for the following loop to build the rest of the heightmap
	verticesPosition = 12;
	indicesPosition = 6;
	int newestVertexIndex = 3;

	PreviousSquare previousSquare;
	previousSquare.bottomLeftIndex = 0;
	previousSquare.bottomRightIndex = 1;
	previousSquare.topRightIndex = 2;
	previousSquare.topLeftIndex = 3;

	PreviousSquare firstSquareInRow;
	firstSquareInRow.bottomLeftIndex = 0;
	firstSquareInRow.bottomRightIndex = 1;
	firstSquareInRow.topRightIndex = 2;
	firstSquareInRow.topLeftIndex = 3;

	/*
	squareOrigin = glm::vec3(settings.origin);
	squareOrigin = squareOrigin + moveDown;

	vertices[24] = squareOrigin[0];
	vertices[25] = squareOrigin[1];
	vertices[26] = squareOrigin[2];

	vertices[27] = squareOrigin[0] + 1.0f;
	vertices[28] = squareOrigin[1];
	vertices[29] = squareOrigin[2];

	indices[18] = 8;
	indices[19] = 9;
	indices[20] = 1;
	indices[21] = 1;
	indices[22] = 0;
	indices[23] = 8;

	squareOrigin += moveRight;

	vertices[30] = squareOrigin[0] + 1.0f;
	vertices[31] = squareOrigin[1];
	vertices[32] = squareOrigin[2];

	indices[24] = 9;
	indices[25] = 10;
	indices[26] = 4;
	indices[27] = 4;
	indices[28] = 1;
	indices[29] = 9;
	*/

	for(int i = 1; i < squareCount; i++){
		//First row squares
		//Shared vertices: bottom left, top left
		//New: bottom right, top right
		if(i < settings.widthDensity){
			squareOrigin = squareOrigin + moveRight;
			addVertex(squareOrigin[0] + 1.0f, squareOrigin[1], squareOrigin[2]);
			newestVertexIndex++;
			addVertex(squareOrigin[0] + 1.0f, squareOrigin[1], squareOrigin[2] + 1.0f);
			newestVertexIndex++;

			addIndex(previousSquare.bottomRightIndex);
			addIndex(newestVertexIndex-1);
			addIndex(newestVertexIndex);
			addIndex(newestVertexIndex);
			addIndex(previousSquare.topRightIndex);
			addIndex(previousSquare.bottomRightIndex);

			previousSquare.bottomLeftIndex = previousSquare.bottomRightIndex;
			previousSquare.bottomRightIndex = newestVertexIndex-1;
			previousSquare.topRightIndex = newestVertexIndex;
			previousSquare.topLeftIndex = previousSquare.topRightIndex;
		}else if(i % settings.widthDensity == 0){
			//First square in row. I.E first column
			//Shared vertices: Top left, top right
			//New vertices: Bottom left, bottom right
			squareOrigin = glm::vec3(settings.origin);
			float column = i / settings.widthDensity;
			squareOrigin += (moveDown * column);

			addVertex(squareOrigin[0], squareOrigin[1], squareOrigin[2]);
			newestVertexIndex++;
			addVertex(squareOrigin[0] + 1.0f, squareOrigin[1], squareOrigin[2]);
			newestVertexIndex++;

			addIndex(newestVertexIndex - 1);
			addIndex(newestVertexIndex);
			addIndex(firstSquareInRow.bottomRightIndex);
			addIndex(firstSquareInRow.bottomRightIndex);
			addIndex(firstSquareInRow.bottomLeftIndex);
			addIndex(newestVertexIndex - 1);
			
			//Do these out of order because they self refer
			firstSquareInRow.topRightIndex = firstSquareInRow.bottomRightIndex;
			firstSquareInRow.topLeftIndex = firstSquareInRow.bottomLeftIndex;

			previousSquare.topRightIndex = firstSquareInRow.bottomRightIndex;
			previousSquare.topLeftIndex = firstSquareInRow.bottomLeftIndex;

			firstSquareInRow.bottomLeftIndex = newestVertexIndex - 1;
			firstSquareInRow.bottomRightIndex = newestVertexIndex;

			previousSquare.bottomLeftIndex = newestVertexIndex -1;
			previousSquare.bottomRightIndex = newestVertexIndex;

		}else{
			//Internal squares (surronded on each side)
			//Shared vertices: bottom left, top right, top left
			//New: bottom right
//			squareOrigin *= moveRight;
//			addVertex(squareOrigin[0] + 1.0f, squareOrigin[1], squareOrigin[2]);
//			newestVertexIndex++;
////
//			addIndex(previousSquare.bottomRightIndex);
//			addIndex(newestVertexIndex);

		}


	}
	

	polygon.setVertices(vertices, 3*4*squareCount);
	polygon.setIndices(indices, 2*3*squareCount);
	polygon.buildStatic();
	polygon.rotate(glm::vec3(-1.0f,0.0f,0.0f), 1.57f);

}
