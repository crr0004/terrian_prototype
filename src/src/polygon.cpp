#include "polygon.h"
#include "matrixstacksingleton.h"
#include "logicstate.h"

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace Terrian_Prototype;

/* -------------------------------*/
/** 
 * @brief A wrapper class for basic opengl buffered index drawing
 * This is to ease the creation of a basic setup for something that draws just triangles.
 *
 * @b Example usage
 * @code
	Polygon triangle; 
##Setup
	triangle.setVertices(triangle_one_vertices, sizeof(triangle_one_vertices) / sizeof(GLfloat));
	triangle.setIndices(triangle_one_indices, sizeof(triangle_one_indices) / sizeof(GLuint));
	triangle.buildStatic();

	triangle.setShaderLocations(vertShaderLocation);

##Drawing
	triangle.update(&logicContext);
	triangle.draw(&logicContext);
	@endcode
 */
/* ---------------------------------*/
Geometry::Polygon::Polygon(){
}


/* -------------------------------*/
/** 
 * @brief Sets the vertices to be used when rendering. Expects 3 elements per vertex
 * @warning Only stores a reference to the vertices. It is up to you to keep it in allocated.
 * @note Might change in the future.
 * 
 * @param vertices[] pointer to the vertices
 * @param size how many elements are in the array
 */
/* ---------------------------------*/
void Geometry::Polygon::setVertices(GLfloat vertices[], unsigned int size){
	vertexSize = size;
	this->vertices = vertices;
}
/* -------------------------------*/
/** 
 * @see Geometry::Polygon::setVertices(GLfloat, unsigned int)
 */
/* ---------------------------------*/
void Geometry::Polygon::setIndices(GLuint indices[], unsigned int size){
	indicesSize = size;
	this->indices = indices;
}
GLfloat* Geometry::Polygon::getVertices(){
	return vertices;
}
GLuint* Geometry::Polygon::getIndices(){
	return indices;
}
glm::mat4* Geometry::Polygon::getModelMatrix(){
	return &model_matrix;
}

void Geometry::Polygon::translate(glm::vec3 moveBy){
	model_matrix = glm::translate(model_matrix, moveBy);
}

void Geometry::Polygon::rotate(glm::vec3 rotateAround, float rotateBy){
	model_matrix = glm::rotate(model_matrix, rotateBy, rotateAround);
}

/* -------------------------------*/
/** 
 * @brief Builds the parts needed to draw static indexed triangles
 */
/* ---------------------------------*/
void Geometry::Polygon::buildStatic(){
	glGenBuffers(2, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(GLuint), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/* -------------------------------*/
/** 
 * @brief Sets the location vec3 in the bound shader.
 * @TODO This really shouldn't need to exist and a shader context should exist
 * 
 * @Param vertShaderLocation
 */
/* ---------------------------------*/
void Geometry::Polygon::setShaderLocations(GLuint vertShaderLocation){
	this->vertShaderLocation = vertShaderLocation;

}

/* -------------------------------*/
/** 
 * @brief Performs the logic for the polygon
 * @note Only stores and updates the model matrix at the moment
 * @warning Only call a polygon's update one at a time after drawing because this pushs the current modelview onto the matrix stack
 * 
 * @param state current logical context containing references to the camera modelview matrix
 */
/* ---------------------------------*/
void Geometry::Polygon::update(struct LogicContext* state){
	MatrixStackSingleton* instance = MatrixStackSingleton::instance();

	instance->push(model_matrix);
	model_matrix = state->modelview * model_matrix;

}

/* -------------------------------*/
/** 
 * @brief Draws the built triangles
 * Binds the passed in arrays to opengl buffers. Binds the needed components for the shader, and draws the polygon
 *
 * @warning Must be directly called after update because it restores the modelview.
 * 
 * @param state @see Geometry::Polygon::draw(struct LogicContext)
 * @TODO Should be usin a shader context rather than the logicContext
 */
/* ---------------------------------*/
void Geometry::Polygon::draw(struct LogicContext* state){
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

Geometry::Polygon::~Polygon(){

}

