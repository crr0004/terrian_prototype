#include "arraybufferbuilder.hpp"
#include <glad/glad.h>


ArrayBufferBuilt* arrayBuffer = 0;

ArrayBufferBuilder::ArrayBufferBuilder(){
	arrayBuffer = new ArrayBufferBuilt();

}

IArrayBufferBuilder* ArrayBufferBuilder::clone(){
	IArrayBufferBuilder* clone = new ArrayBufferBuilder();

	return clone;
}

void ArrayBufferBuilder::setArrayCount(GLsizei count){
	arrayBuffer->arrayCount = count;
}

void ArrayBufferBuilder::setVerticesPoint(const GLvoid*){
	arrayBuffer->
}

void ArrayBufferBuilder::setMode(GLenum){
	arrayBuffer->
}

void ArrayBufferBuilder::setFirst(GLint){
	arrayBuffer->
}

void ArrayBufferBuilder::setTarget(GLenum){
	arrayBuffer->
}

void ArrayBufferBuilder::setBufferSize(GLsizeiptr){
	arrayBuffer->
}

void ArrayBufferBuilder::setDrawUsage(GLenum){
	arrayBuffer->
}

ArrayBufferBuilder::~ArrayBufferBuilder(){
	if(arrayBuffer != 0){
		delete arrayBuffer;
	}
}

