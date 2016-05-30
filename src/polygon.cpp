#include "polygon.h"
#include <stdio.h>

Polygon::Polygon(){

}

void Polygon::setVertices(GLfloat vertices[], unsigned int size){
	vertexSize = size;
	this->vertices = vertices;
}

void Polygon::setIndices(GLuint indices[], unsigned int size){
	indicesSize = size;
	this->indices = indices;
}

void Polygon::buildStatic(){
	glGenBuffers(2, &vboID[0]);
	printf("Array ids: %d %d\n", vboID[0], vboID[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Polygon::setShaderLocations(GLuint vertShaderLocation){
	this->vertShaderLocation = vertShaderLocation;

}

void Polygon::draw(){
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
		glEnableVertexAttribArray(vertShaderLocation);

		glVertexAttribPointer(
				vertShaderLocation,
				3, //size of attribute
				GL_FLOAT,
				GL_FALSE,
				0, //stride
				(void*)0 //Pointer to the off of the first component of the first element
				);
		glDrawElements(
				GL_TRIANGLES,
				6, //Amount of vertices to draw
				GL_UNSIGNED_INT,
				(void*)0
				);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(vertShaderLocation);
}

Polygon::~Polygon(){

}

