#include "renderfactory.hpp"
#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"

IDrawBuilder* RenderFactory::drawBuilderPrototype = 0;
IVertexAttributeBuilder* RenderFactory::vertexBuilderPrototype = 0;
IArrayBufferBuilder* RenderFactory::arrayBuilderPrototype = 0;

RenderFactory::RenderFactory(){

}

RenderFactory::~RenderFactory(){

}
void RenderFactory::setPrototypes(
		IVertexAttributeBuilder* vertBuilder,
		IArrayBufferBuilder* arrayBuilder,
		IDrawBuilder* drawBuilder
		){
	
	RenderFactory::drawBuilderPrototype = drawBuilder;
	RenderFactory::vertexBuilderPrototype = vertBuilder;
	RenderFactory::arrayBuilderPrototype = arrayBuilder;

}


IArrayBufferBuilder* RenderFactory::NewArrayBufferBuilder(){

	return arrayBuilderPrototype->clone();
}

IVertexAttributeBuilder* RenderFactory::NewVertexAttributeBuilder(){

	return vertexBuilderPrototype->clone();
}

IDrawBuilder* RenderFactory::NewDrawBuilder(){

	return drawBuilderPrototype->clone();
}
