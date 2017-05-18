#include <catch.hpp>
#include <fakeit.hpp>
#include "node.hpp"
#include "geometry/moveable.hpp"

using namespace fakeit;
TEST_CASE("Visit double dispatch works"){
	using namespace Geometry;
	INode* node1 = new Moveable();
	Mock<Geometry::Moveable> mockMoveable;
	Fake(OverloadedMethod(mockMoveable, visit, int(Moveable*)));
	Fake(OverloadedMethod(mockMoveable, visit, int(INode*)));
	INode* node2 = (INode*)&mockMoveable.get();
	node1->visit(node2);
	Verify(OverloadedMethod(mockMoveable, visit, int(Moveable*)));
}
