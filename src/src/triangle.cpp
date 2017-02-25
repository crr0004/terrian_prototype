#include "triangle.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "matrixstacksingleton.hpp"
#include "logicstate.hpp"
#include "RenderFactory.hpp"
#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"

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
void Triangle::setVertices(GLfloat vertices[], unsigned int size){
	this->vertices = vertices;
	vertexSize = size;
}
GLfloat* Triangle::getVertices(){
	return vertices;
}
unsigned int Triangle::getVertexSize(){
	return vertexSize;
}
void Triangle::buildStatic(){
	glGenBuffers(1, &vboID[0]);

	IVertexAttributeBuilder* vertBuilder = RenderFactory::NewVertexAttributeBuilder();
	vertBuilder->setLocation(vertShaderLocation);
	vertBuilder->setType(GL_FLOAT);
	vertBuilder->setSetNormalized(GL_FALSE);
	vertBuilder->setAttributeSize(3);
	vertBuilder->setStride(0);
	vertBuilder->setOffset(0);

	IArrayBufferBuilder* arrayDraw = RenderFactory::NewArrayBufferBuilder();
	arrayDraw->numberOfArrays(1);
	arrayDraw->setSize(vertexSize);
	arrayDraw->setVertices(vertices);
	arrayDraw->setType(GL_TRIANGLES);
	arrayDraw->setStartingIndex(0);

	IDrawBuilder* draw = RenderFactory::NewDrawBuilder();
	draw->addVertexAttribute(vertBuilder->build());
	draw->addArrayBuffer(arrayDraw->build());
	
}
void Triangle::setShaderLocations(GLuint vertShaderLocation){
	this->vertShaderLocation = vertShaderLocation;
}
void Triangle::setShaderLocations(const char* name){
	GLint shaderProgram;
	glGetIntegerv(GL_CURRENT_PROGRAM,&shaderProgram);
	this->vertShaderLocation = glGetAttribLocation(shaderProgram, name);
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
			GL_TRIANGLES,
			0,
			vertexSize //Amount of indices to draw
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
