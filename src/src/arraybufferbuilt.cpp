#include "arraybufferbuilder.hpp"
#include <glad/glad.h>

ArrayBufferBuilt::ArrayBufferBuilt(){
	buffered = false;
}

ArrayBufferBuilt::~ArrayBufferBuilt(){

}

void ArrayBufferBuilt::setBufferID(GLuint id){
	this->id = id;
}

void ArrayBufferBuilt::draw(){
	glDrawArrays(drawMode, first, arrayCount);
}

void ArrayBufferBuilt::enable(){
	glBindBuffer(target, id);
}

void ArrayBufferBuilt::buffer(){
	if(!buffered || drawUsage == GL_DYNAMIC_DRAW){
		glBufferData(target, bufferSize, source, drawUsage);
	}

}

void ArrayBufferBuilt::disable(){
	glBindBuffer(target, 0);
}

