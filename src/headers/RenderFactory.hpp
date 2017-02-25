#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H
#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"
class RenderFactory {
	public:
		static IVertexAttributeBuilder* NewAttributeBuilder();
		static IArrayBufferBuilder* NewArrayBufferBuilder();
		static IDrawBuilder* NewDrawBuilder();
		RenderFactory();
		~RenderFactory();
};
#endif
