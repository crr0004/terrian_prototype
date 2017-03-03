#include "vertexattributebuilder.hpp"
#include <glad/glad.h>


VertexAttributeBuilt::VertexAttributeBuilt(){

}

VertexAttributeBuilt::~VertexAttributeBuilt(){
}

void VertexAttributeBuilt::enable(){
	glEnableVertexAttribArray(location);

}

void VertexAttributeBuilt::bind(){
	glVertexAttribPointer(
			location,
			size, //size of attribute
			type,
			normalized,
			stride, //stride
			(void*)offset //Pointer to the off of the first component of the first element
			);
}

void VertexAttributeBuilt::disable(){
	glDisableVertexAttribArray(location);
}
