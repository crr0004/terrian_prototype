#include "renderfactory.hpp"
#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"

IDrawBuilder* RenderFactory::drawBuilderPrototype = 0;

RenderFactory::RenderFactory(){

}

RenderFactory::~RenderFactory(){

}
void RenderFactory::setPrototypes(
		IVertexAttributeBuilder* vertBuilder,
		IArrayBufferBuilder* arrayBuilder,
		IDrawBuilder* drawBuilder){
	RenderFactory::drawBuilderPrototype = drawBuilder;

}


IArrayBufferBuilder* RenderFactory::NewArrayBufferBuilder(){

	return 0;
}

IVertexAttributeBuilder* RenderFactory::NewAttributeBuilder(){

	return 0;
}

IDrawBuilder* RenderFactory::NewDrawBuilder(){

	return drawBuilderPrototype->clone();
}
