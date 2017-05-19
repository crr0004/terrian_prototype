#include "circle.hpp"
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"
using namespace Geometry;

Circle::Circle(){
	int segments = 20;
	vertexSize = segments*3;
	vertices = new GLfloat[vertexSize];
	GLfloat twicePi = 2.0f * std::acos(-1);

	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLfloat radius = 1.8f;
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = 0.0f;
	for(int i = 0; i < segments; i++){
		vertices[(i*3)+0] = x + (radius *std::cos(i*twicePi/segments));
		vertices[(i*3)+1] = y + (radius *std::sin(i*twicePi/segments));
		vertices[(i*3)+2] = 0.0f;
		fmt::printf("i is %d\n", i);
	}
}
void Circle::buildStatic(){
	glGenBuffers(1, &vboID[0]);
}
void Circle::draw(){
	/*
	fmt::printf("Drawing triangle at X,Y,Z: (%f,%f,%f)\n",
			model_matrix[3][0],
			model_matrix[3][1],
			model_matrix[3][2]
			);
			*/

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
			GL_LINE_LOOP,
			0,
			vertexSize/3 //Amount of indices to draw
			);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(vertShaderLocation);
	model_matrix = (MatrixStackSingleton::instance())->pop();
}
Circle::~Circle(){
	delete vertices;
}
