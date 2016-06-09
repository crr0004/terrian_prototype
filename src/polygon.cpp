#include "polygon.h"
#include "matrixstacksingleton.h"
#include "logicstate.h"

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
glm::mat4* Polygon::getModelMatrix(){
	return &model_matrix;
}

void Polygon::translate(glm::vec3 moveBy){
	model_matrix = glm::translate(model_matrix, moveBy);
}

void Polygon::buildStatic(){
	glGenBuffers(2, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Polygon::setShaderLocations(GLuint vertShaderLocation){
	this->vertShaderLocation = vertShaderLocation;

}

void Polygon::update(struct LogicContext* state){
	MatrixStackSingleton* instance = MatrixStackSingleton::instance();

	instance->push(model_matrix);
	model_matrix = state->modelview * model_matrix;

}

void Polygon::draw(struct LogicContext* state){
		glUniformMatrix4fv(state->uloc_modelview, 1, GL_FALSE, glm::value_ptr(model_matrix));
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
				indicesSize, //Amount of vertices to draw
				GL_UNSIGNED_INT,
				(void*)0
				);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(vertShaderLocation);
		model_matrix = (MatrixStackSingleton::instance())->pop();
}

Polygon::~Polygon(){

}

