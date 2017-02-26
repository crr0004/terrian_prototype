#include <catch.hpp>
#include <fakeit.hpp>
#include "renderfactory.hpp"

#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"

TEST_CASE("RenderFactory basic usage"){
	SECTION("Setting prototypes"){
		RenderFactory* factory = new RenderFactory();
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
