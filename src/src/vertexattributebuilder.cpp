#include "vertexattributebuilder.hpp"
#include <glad/glad.h>

VertexAttributeBuilt* vertex = 0;

VertexAttributeBuilder::VertexAttributeBuilder(){
	vertex = new VertexAttributeBuilt();
}

VertexAttributeBuilder::~VertexAttributeBuilder(){
	delete vertex;
}

IVertexAttributeBuilder* VertexAttributeBuilder::clone(){
	VertexAttributeBuilder *clone = new VertexAttributeBuilder();

	return clone;
}

void VertexAttributeBuilder::setLocation(GLuint location){
	vertex->location = location;
}

void VertexAttributeBuilder::setType(GLenum type){
	vertex->type = type;
}

void VertexAttributeBuilder::setSetNormalized(GLboolean normalized){
	vertex->normalized = normalized;

}

void VertexAttributeBuilder::setAttributeSize(GLint size){
	vertex->size = size;

}

void VertexAttributeBuilder::setStride(GLsizei stride){
	vertex->stride = stride;

}

void VertexAttributeBuilder::setOffset(const GLvoid* offset){
	vertex->offset = offset;

}

IVertexAttributeBuilt* VertexAttributeBuilder::build(){
	return (IVertexAttributeBuilt*)vertex;
}
