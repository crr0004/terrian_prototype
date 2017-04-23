#include "matrixstacksingleton.hpp"
#include <cassert>
#include <stdio.h>

struct LinkedMatrix{
	//We won't use a pointer because this means this stack will keep the matrix within scope
	glm::mat4 me;
	struct LinkedMatrix* prev;
};

MatrixStackSingleton* MatrixStackSingleton::_instance = 0;

struct LinkedMatrix* _head = 0;

MatrixStackSingleton* MatrixStackSingleton::instance(){
    if(_instance == 0){
    	_instance = new MatrixStackSingleton;
    }
    return _instance;
}
void MatrixStackSingleton::Destroy(){
	if(_instance != 0){
		delete _instance;
	}
}

MatrixStackSingleton::MatrixStackSingleton(){
}
MatrixStackSingleton::~MatrixStackSingleton(){
	if(_head != 0){
		delete _head;
	}
}
glm::mat4 MatrixStackSingleton::push(glm::mat4 m){
	struct LinkedMatrix* newHead = new LinkedMatrix;
	newHead->me = m;
	//Will the current head now fall out of scope?
	newHead->prev = _head;
	_head = newHead;
	return glm::mat4(m);
}

glm::mat4 MatrixStackSingleton::pop(){
	glm::mat4 oldMatrx = _head->me;
	struct LinkedMatrix *old = _head;
	_head = _head->prev;

	old->prev = 0;
	delete old;
	
	return oldMatrx;
}
