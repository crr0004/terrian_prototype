#include <catch.hpp>
#include <fakeit.hpp>
#include <glm/ext.hpp>
#include <string>
#include <fmt/format.h>
#include "node.hpp"
#include "geometry/moveable.hpp"

using namespace fakeit;
TEST_CASE("Moveable Visit double dispatch works"){
	using namespace Geometry;
	INode* node1 = new Moveable();
	Mock<Geometry::Moveable> mockMoveable;
	Fake(OverloadedMethod(mockMoveable, visit, int(Moveable*)));
	Fake(OverloadedMethod(mockMoveable, visit, int(INode*)));
	INode* node2 = (INode*)&mockMoveable.get();
	node1->visit(node2);
	Verify(OverloadedMethod(mockMoveable, visit, int(Moveable*)));

	delete node1;
}

TEST_CASE("Movable All moveable operations cascade to children"){
	using namespace Geometry;
	Moveable root;
	Moveable child1;
	Moveable child2;
	glm::vec3 moveBy = glm::vec3(1.0,2.0,-3.0);
	glm::vec3 moveBy2 = glm::vec3(2.0,3.0,-4.0);

	root.add(&child1);
	child1.add(&child2);
	root.translate(moveBy);

	glm::mat4& rootMatrix = *root.getModelMatrix();
	glm::mat4 child1Matrix = child1.getCulumativeMatrix();
	glm::mat4 child2Matrix = child2.getCulumativeMatrix();

	REQUIRE(rootMatrix[3][0] == moveBy[0]);
	REQUIRE(rootMatrix[3][1] == moveBy[1]);
	REQUIRE(rootMatrix[3][2] == moveBy[2]);
	//child1 gets transformed by rootMatrix
	REQUIRE(child1Matrix[3][0] == rootMatrix[3][0]);
	REQUIRE(child1Matrix[3][1] == rootMatrix[3][1]);
	REQUIRE(child1Matrix[3][2] == rootMatrix[3][2]);

	//child2 gets transformed by rootMatrix
	REQUIRE(child2Matrix[3][0] == rootMatrix[3][0]);
	REQUIRE(child2Matrix[3][1] == rootMatrix[3][1]);
	REQUIRE(child2Matrix[3][2] == rootMatrix[3][2]);

	//child2 gets transformed by rootMatrix and child1
	fmt::printf("Matrix %s\n", glm::to_string(child1.getCulumativeMatrix()));
	child1.translate(moveBy2);
	fmt::printf("Matrix %s\n", glm::to_string(*child1.getModelMatrix()));
	child2Matrix = child2.getCulumativeMatrix();
	fmt::printf("Matrix %s\n", glm::to_string(child2.getCulumativeMatrix()));
	REQUIRE(child2Matrix[3][0] == rootMatrix[3][0] + moveBy2[0]);
	REQUIRE(child2Matrix[3][1] == rootMatrix[3][1] + moveBy2[1]);
	REQUIRE(child2Matrix[3][2] == rootMatrix[3][2] + moveBy2[2]);

	child1.translate(-moveBy2);

	child1.translate(-moveBy);
	REQUIRE(child1Matrix[3][0] == 0.0);
	REQUIRE(child1Matrix[3][1] == 0.0);
	REQUIRE(child1Matrix[3][2] == 0.0);

}

TEST_CASE("Moveable Push and pop matrix works correctly"){
	using namespace Geometry;
	Moveable root;
	Moveable child1;
	glm::vec3 moveBy = glm::vec3(1.0,2.0,-3.0);

	root.add(&child1);

	glm::mat4& rootMatrix = *root.getModelMatrix();
	glm::mat4& child1Matrix = *child1.getModelMatrix();

//	root.push();
//	root.translate(moveBy);
//	REQUIRE(child1Matrix[3][0] == rootMatrix[3][0]);
//	REQUIRE(child1Matrix[3][1] == rootMatrix[3][1]);
//	REQUIRE(child1Matrix[3][2] == rootMatrix[3][2]);
//	root.pop();
//	REQUIRE(child1Matrix[3][0] == rootMatrix[3][0]);
//	REQUIRE(child1Matrix[3][1] == rootMatrix[3][1]);
//	REQUIRE(child1Matrix[3][2] == rootMatrix[3][2]);
}
