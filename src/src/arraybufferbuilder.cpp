#include "arraybufferbuilder.hpp"
#include <glad/glad.h>



ArrayBufferBuilt* arrayBuffer = 0;

ArrayBufferBuilder::ArrayBufferBuilder(){
	arrayBuffer = new ArrayBufferBuilt();
}

ArrayBufferBuilder::~ArrayBufferBuilder(){
	if(arrayBuffer != 0){
		delete arrayBuffer;
	}
}

IArrayBufferBuilder* ArrayBufferBuilder::clone(){
	IArrayBufferBuilder* clone = new ArrayBufferBuilder();

	return clone;
}

void ArrayBufferBuilder::setArrayCount(GLsizei count){
	arrayBuffer->arrayCount = count;
}

void ArrayBufferBuilder::setSource(GLvoid* source){
	arrayBuffer->source = source;
}

void ArrayBufferBuilder::setMode(GLenum mode){
	arrayBuffer->mode = mode;
}

void ArrayBufferBuilder::setFirst(GLint first){
	arrayBuffer->first = first;
}

void ArrayBufferBuilder::setTarget(GLenum target){
	arrayBuffer->target = target;
}

void ArrayBufferBuilder::setBufferSize(GLsizeiptr bufferSize){
	arrayBuffer->bufferSize = bufferSize;
}

void ArrayBufferBuilder::setDrawUsage(GLenum drawUsage){
	arrayBuffer->drawUsage = drawUsage;
}
