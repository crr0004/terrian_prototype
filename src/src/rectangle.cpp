#include "rectangle.hpp"
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"

using namespace Geometry;
Rectangle::Rectangle(){
	vertexSize = 18;
	vertices = new GLfloat[vertexSize];
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;

	vertices[3] = 1.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	vertices[6] = 1.0f;
	vertices[7] = 1.0f;
	vertices[8] = 0.0f;

	
	vertices[9] = 0.0f;
	vertices[10] = 0.0f;
	vertices[11] = 0.0f;

	vertices[12] = 1.0f;
	vertices[13] = 1.0f;
	vertices[14] = 0.0f;

	vertices[15] = 0.0f;
	vertices[16] = 1.0f;
	vertices[17] = 0.0f;
}
void Rectangle::buildStatic(){
	glGenBuffers(1, &vboID[0]);
}
void Rectangle::setLengths(float a, float b){
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;

	vertices[3] = a;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	vertices[6] = a;
	vertices[7] = b;
	vertices[8] = 0.0f;

	
	vertices[9] = 0.0f;
	vertices[10] = 0.0f;
	vertices[11] = 0.0f;

	vertices[12] = a;
	vertices[13] = b;
	vertices[14] = 0.0f;

	vertices[15] = 0.0f;
	vertices[16] = b;
	vertices[17] = 0.0f;

}
void Rectangle::draw(){

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(state->uloc_modelview, 1, GL_FALSE, glm::value_ptr(*moveable.getModelMatrix()));
	glEnableVertexAttribArray(vertShaderLocation);

	glVertexAttribPointer(
			vertShaderLocation,
			3, //size of attribute
			GL_FLOAT,
			GL_FALSE,
			0, //stride
			(void*)0 //Pointer to the off of the first component of the first element
			);
	glDrawArrays(
			GL_TRIANGLES,
			0,
			vertexSize //Amount of indices to draw
			);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(vertShaderLocation);
	moveable.pop();
}
Rectangle::~Rectangle(){
	delete vertices;
}
