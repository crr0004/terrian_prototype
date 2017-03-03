#ifndef RENDERFACTORY_H
#define RENDERFACTORY_H
#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"
class RenderFactory {
	public:
		static IVertexAttributeBuilder* NewVertexAttributeBuilder();
		static IArrayBufferBuilder* NewArrayBufferBuilder();
		static IDrawBuilder* NewDrawBuilder();
		RenderFactory();
		~RenderFactory();
		void setPrototypes(IVertexAttributeBuilder*,
				IArrayBufferBuilder*,
				IDrawBuilder*);

	protected:
		static IVertexAttributeBuilder* vertexBuilderPrototype;
		static IArrayBufferBuilder* arrayBuilderPrototype;
		static IDrawBuilder* drawBuilderPrototype;

};
#endif
