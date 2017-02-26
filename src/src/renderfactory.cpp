#include "renderfactory.hpp"
#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"

RenderFactory::RenderFactory(){

}

RenderFactory::~RenderFactory(){

}
void RenderFactory::setPrototypes(
		IVertexAttributeBuilder* vertBuilder,
		IArrayBufferBuilder* arrayBuilder,
		IDrawBuilder* drawBuilder){

}


IArrayBufferBuilder* RenderFactory::NewArrayBufferBuilder(){

	return 0;
}

IVertexAttributeBuilder* RenderFactory::NewAttributeBuilder(){

	return 0;
}

IDrawBuilder* RenderFactory::NewDrawBuilder(){

	return 0;
}


