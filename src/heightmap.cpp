#include "heightmap.h"
#include <GLFW/glfw3.h>
using namespace Heightmap;

void build(struct HeightmapSettings settings){
	int squareCount = settings.widthDensity*settings.widthDensity;
	//@TODO: these should be allocated outside here
	GLfloat vertices[3*4*squareCount]; //3 is elements. 4 is for square
	GLuint indices[2*3*squareCount];//2 triangles per square, 3 indices per triangle

	//this should be calculated from the map origin and the map extents
	glm::vec3 squareOrigin = glm::vec3(0.0f, 0.0f, 0.0f);
	//Vector to move right
	glm::vec3 moveRight = glm::vec3(1.0f, 0.0f, 0.0f);
	//Vector to move down
	glm::vec3 moveDown = glm::vec3(0.0f, 0.0f, 1.0f);

	//Generate first square outside loop	
	//move into a general function
	vertices[0] = squareOrigin[0];
	vertices[1] = squareOrigin[1];
	vertices[2] = squareOrigin[2];



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

}
