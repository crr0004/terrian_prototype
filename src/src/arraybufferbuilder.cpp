#include "arraybufferbuilder.hpp"
#include <glad/glad.h>

ArrayBufferBuilder::ArrayBufferBuilder(){

	arraybuilt = new ArrayBufferBuilt();
}

ArrayBufferBuilder::~ArrayBufferBuilder(){
	if(arraybuilt != 0){
		delete arraybuilt;
	}

}

IArrayBufferBuilder* ArrayBufferBuilder::clone(){
	IArrayBufferBuilder* clone = new ArrayBufferBuilder();

	return clone;
}

void ArrayBufferBuilder::setArrayCount(GLsizei count){
	arraybuilt->arrayCount = count;
}

void ArrayBufferBuilder::setSource(const GLvoid* source){
	arraybuilt->source = source;
}

void ArrayBufferBuilder::setMode(GLenum mode){
	arraybuilt->mode = mode;
}

void ArrayBufferBuilder::setFirst(GLint first){
	arraybuilt->first = first;
}

void ArrayBufferBuilder::setTarget(GLenum target){
	arraybuilt->target = target;
}

void ArrayBufferBuilder::setBufferSize(GLsizeiptr bufferSize){
	arraybuilt->bufferSize = bufferSize;
}

void ArrayBufferBuilder::setDrawUsage(GLenum drawUsage){
	arraybuilt->drawUsage = drawUsage;
}
