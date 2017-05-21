#include "geometry/moveable.hpp"
#include "matrixstacksingleton.hpp"
#include <fmt/format.h>
#include <cstddef>
using namespace Geometry;


Moveable::Moveable(){
	transitiveMatrix = glm::mat4(1.0);
	parent = NULL;
}

void Moveable::operation(){
	for(int i = 0; i < children.size(); i++){
		//we do the cast so the double dispatch actually works
		//without it, it would go straight into the concrete visit for
		//moveable
		children.at(i)->visit((INode*)this);
	}
}
int Moveable::visit(INode* node){
	node->visit(this);
	return 0;
}

int Moveable::visit(Moveable* node){
	node->translate(transitiveMatrix);

	return 0;
}
void Moveable::translate(glm::vec3 moveBy){
	glm::mat4 matrix(1.0);
	matrix = glm::translate(matrix, moveBy);
	this->translate(matrix);
}
void Moveable::rotate(glm::vec3 rotateAround, float rotateBy){
	glm::mat4 matrix(1.0);
	matrix = glm::rotate(matrix, rotateBy, rotateAround);
	this->translate(matrix);
}
glm::mat4* Moveable::getModelMatrix(){
	return &model_matrix;
}

void Moveable::translate(glm::mat4& moveBy){
	model_matrix = moveBy * model_matrix;
	transitiveMatrix = moveBy * transitiveMatrix;
	this->operation();
	transitiveMatrix = glm::mat4(1.0);
}
void Moveable::push(){
	model_matrix = (MatrixStackSingleton::instance())->push(model_matrix);
}

void Moveable::pop(){
	model_matrix = (MatrixStackSingleton::instance())->pop();
}

Moveable::~Moveable(){

}
