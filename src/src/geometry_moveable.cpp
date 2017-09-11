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

void Moveable::add(INode* node){
	children.push_back(node);
	operation();
}

int Moveable::visit(Moveable* node){
	node->parentTranslate(model_matrix * transitiveMatrix);
	return 0;
}
void Moveable::translate(glm::vec3 moveBy){
	model_matrix = glm::translate(model_matrix, moveBy);
	operation();
}
void Moveable::rotate(glm::vec3 rotateAround, float rotateBy){
	model_matrix = glm::rotate(model_matrix, rotateBy, rotateAround);
	operation();
}
void Moveable::setPos(glm::vec3 newPos){
	model_matrix[3][0] = newPos.x;
	model_matrix[3][1] = newPos.y;
	model_matrix[3][2] = newPos.z;

}
glm::mat4* Moveable::getModelMatrix(){
	return &model_matrix;
}
void Moveable::translate(glm::mat4& moveBy){
	model_matrix = model_matrix * moveBy;
}
void Moveable::parentTranslate(glm::mat4 moveBy){
	transitiveMatrix = glm::mat4(moveBy);
	operation();
}
glm::mat4 Moveable::getCulumativeMatrix(){
	return transitiveMatrix * model_matrix;
}
glm::mat4* Moveable::getTransitiveMatrix(){
	return &transitiveMatrix;
}
void Moveable::push(){
	model_matrix = (MatrixStackSingleton::instance())->push(model_matrix);
}

void Moveable::pop(){
	model_matrix = (MatrixStackSingleton::instance())->pop();
}

Moveable::~Moveable(){

}
