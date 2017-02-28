#include <catch.hpp>
#include <fakeit.hpp>
#include "renderfactory.hpp"

#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"

TEST_CASE("RenderFactory basic usage"){
	SECTION("Setting prototypes"){
		using namespace fakeit;
		RenderFactory* factory = new RenderFactory();
		Mock<IDrawBuilder> drawMock;
		Mock<IArrayBufferBuilder> arrayMock;
		Mock<IVertexAttributeBuilder> vertexMock;

		IDrawBuilder &drawBuilder = drawMock.get();
		IArrayBufferBuilder &arrayBuilder = arrayMock.get();
		IVertexAttributeBuilder &vertBuilder = vertexMock.get();

		factory->setPrototypes(
				&vertBuilder,
				&arrayBuilder,
				&drawBuilder);
		When(Method(drawMock,clone)).Return(&drawBuilder);

		IDrawBuilder *drawBuilderMock = RenderFactory::NewDrawBuilder();

		Verify(Method(drawMock,clone));


		//When(Method(mock,foo))
		/*
Mock<SomeInterface> mock;

When(Method(mock,foo)).Return(0);

SomeInterface &i = mock.get();

// Production code
i.foo(1);

// Verify method mock.foo was invoked.
Verify(Method(mock,foo));

// Verify method mock.foo was invoked with specific arguments.
Verify(Method(mock,foo).Using(1));
		factory->setPrototypes(
				new StubVertexBuilder(), 
				new StubArrayBufferBuilder(), 
				new StubDrawBuilder()
				);

*/
	}

}
