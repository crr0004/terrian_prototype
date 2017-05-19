#include "line.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"

using namespace Geometry;

Line::Line(){
	vertices = new GLfloat[6];
}
void Line::setStartEnd(const glm::vec3 a, const glm::vec3 b){
	vertices[0] = a[0];
	vertices[1] = a[1];
	vertices[2] = a[2];

	vertices[3] = b[0];
	vertices[4] = b[1];
	vertices[5] = b[2];
	setVertices(vertices, 2*3);

}
void Line::buildStatic(){
	glGenBuffers(1, &vboID[0]);
}
void Line::draw(){
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

	glUniformMatrix4fv(state->uloc_modelview, 1, GL_FALSE, glm::value_ptr(model_matrix));
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
			GL_LINES,
			0,
			vertexSize //Amount of vertices to draw
			);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(vertShaderLocation);
	model_matrix = (MatrixStackSingleton::instance())->pop();

}
Line::~Line(){
	delete[] vertices;
}
