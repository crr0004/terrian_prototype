#include "triangle.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrixstacksingleton.hpp"
#include "logicstate.hpp"

Triangle::Triangle(){
	vertices = new GLfloat[9];
}
void Triangle::setFirstPoint(const glm::vec3 p){
	vertices[0] = p[0];
	vertices[1] = p[1];
	vertices[2] = p[2];
}
void Triangle::setSecondPoint(const glm::vec3 p){
	vertices[3] = p[0];
	vertices[4] = p[1];
	vertices[5] = p[2];
}
void Triangle::setThirdPoint(const glm::vec3 p){
	vertices[6] = p[0];
	vertices[7] = p[1];
	vertices[8] = p[2];
}
void Triangle::setVertices(GLfloat vertices[], unsigned int size){
	this->vertices = vertices;
	vertexSize = size;
}
GLfloat* Triangle::getVertices(){
	return vertices;
}
void Triangle::buildStatic(){
	glGenBuffers(1, &vboID[0]);
}
void Triangle::setShaderLocations(GLuint vertShaderLocation){
	this->vertShaderLocation = vertShaderLocation;
}
void Triangle::draw(struct LogicContext* state){
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
void Triangle::update(struct LogicContext* state){
	MatrixStackSingleton* instance = MatrixStackSingleton::instance();

	instance->push(model_matrix);
	model_matrix = state->modelview * model_matrix;

}
void Triangle::translate(glm::vec3 moveBy){
	model_matrix = glm::translate(model_matrix, moveBy);
}
void Triangle::rotate(glm::vec3 rotateAround, float rotateBy){
	model_matrix = glm::rotate(model_matrix, rotateBy, rotateAround);
}
glm::mat4* Triangle::getModelMatrix(){
	return &model_matrix;

}
Triangle::~Triangle(){
	delete vertices;
}
