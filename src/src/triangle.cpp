#include "triangle.hpp"
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"

using namespace Geometry;
Triangle::Triangle(){
	vertices = new GLfloat[9];
	vertexSize = 9;
	vertices[0] = -1.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;

	vertices[3] = 1.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	vertices[6] = 1.0f;
	vertices[7] = 1.0f;
	vertices[8] = 0.0f;
}
void Triangle::buildStatic(){
	glGenBuffers(1, &vboID[0]);
}
void Triangle::draw(){

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
Triangle::~Triangle(){
	delete vertices;
}
