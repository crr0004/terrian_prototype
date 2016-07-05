#include "heightmap.h"
#include <catch.hpp>
#include <stdio.h>

TEST_CASE("Heightmap"){

	GLuint* indices = new GLuint[54];
	GLfloat* vertices = new GLfloat[27];

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;

	indices[6] = 1;
	indices[7] = 4;
	indices[8] = 5;
	indices[9] = 5;
	indices[10] = 3;
	indices[11] = 1;

	indices[12] = 12;
	indices[13] = 18;
	indices[14] = 21;
	indices[15] = 21;
	indices[16] = 15;
	indices[17] = 12;

	indices[18] = 24;
	indices[19] = 27;
	indices[20] = 1;
	indices[21] = 1;
	indices[22] = 0;
	indices[23] = 24;

	indices[24] = 27;
	indices[29] = 27;	
	HeightmapName::Heightmap heightmap(vertices, indices);

	SECTION("getIndexOfSquare"){
		
		int s0 = heightmap.getIndexOfSquare(1);
		REQUIRE(s0 == 0);
		int s3 = heightmap.getIndexOfSquare(3);
		REQUIRE(s3 == 12);
		int s5 = heightmap.getIndexOfSquare(5);
		REQUIRE(s5 == 27);
	}
	SECTION("getIndexOfSquareVertex"){
		int v3 = heightmap.getIndexOfSquareVertex(3, 3);
		int v2 = heightmap.getIndexOfSquareVertex(3, 2);
		int v1 = heightmap.getIndexOfSquareVertex(3, 1);
		//21 is the start of the eighth vertex
		REQUIRE(v3 == 21);
		REQUIRE(v2 == 18);
		REQUIRE(v1 == 12);

	}

}
