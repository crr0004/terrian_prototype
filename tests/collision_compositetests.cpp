#include <catch.hpp>
#include <fakeit.hpp>
#include <fmt/format.h>
#include "node.hpp"
#include "collision/aabbcollider.hpp"
#include "collision/collider.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
TEST_CASE("AABBCollider test"){
	using namespace Collision;
	float* vertices = new float[9];
	int vertexSize = 9;

	vertices[0] = -1.0f;
	vertices[1] = 0.0f;
	vertices[2] = 0.0f;

	vertices[3] = 1.0f;
	vertices[4] = 0.0f;
	vertices[5] = 0.0f;

	vertices[6] = 1.0f;
	vertices[7] = 1.0f;
	vertices[8] = 0.0f;

	glm::vec3 min = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 max = glm::vec3(1.0f, 1.0f, 1.0f);
	AABBCollider* triangleAABB = new AABBCollider(min, max);

	min = glm::vec3(0.0f, 0.0f, 0.0f);
	max = glm::vec3(2.0f, 2.0f, 2.0f);
	AABBCollider* triangleAABB2 = new AABBCollider(min, max);

	min = glm::vec3(3.0f, 3.0f, 3.0f);
	max = glm::vec3(4.0f, 4.0f, 4.0f);

	REQUIRE(triangleAABB->collides(*triangleAABB2));
	//Generic collides
	Collider* triangleAABB3 = new AABBCollider(min, max);
	REQUIRE(!triangleAABB->visitCollide(triangleAABB3));

}

#include "collision/spherecollider.hpp"
TEST_CASE("Sphere and AABBCollider test"){
	using namespace Collision;
	glm::vec3 min = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 max = glm::vec3(1.0f, 1.0f, 1.0f);
	AABBCollider* triangleAABB = new AABBCollider(min, max);

	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	float radius = 5.0f;
	SphereCollider* sphereCollider = new SphereCollider(center, radius);
	REQUIRE(sphereCollider->visitCollide(triangleAABB));
	REQUIRE(triangleAABB->visitCollide(sphereCollider));

	center = glm::vec3(10.0f, 10.0f, 0.0f);
	radius = 1.0f;
	SphereCollider* sphereCollider2 = new SphereCollider(center, radius);
	REQUIRE(!sphereCollider2->visitCollide(triangleAABB));
	REQUIRE(!triangleAABB->visitCollide(sphereCollider2));

}

#include "collision/simpleworld.hpp"
TEST_CASE("Simpleworld test"){
	using namespace Collision;
	SimpleWorld *root = new SimpleWorld();

	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	float radius = 5.0f;
	SphereCollider* sphere = new SphereCollider(center, radius);

	glm::vec3 min = glm::vec3(3.0f, 3.0f, 3.0f);
	glm::vec3 max = glm::vec3(4.0f, 4.0f, 4.0f);
	AABBCollider* aabb = new AABBCollider(min, max);

	root->add(aabb);
	root->add(sphere);
	using namespace fakeit;
	Mock<AABBCollider> aabbStub;
	When(OverloadedMethod(aabbStub,visitCollide,bool(Collider*))).AlwaysReturn(false);
	When(OverloadedMethod(aabbStub,visitCollide,bool(SphereCollider*))).AlwaysReturn(false);
	When(OverloadedMethod(aabbStub,visitCollide,bool(AABBCollider*)).Using(aabb)).Return(true);
	Fake(Method(aabbStub, setParent));
	//Fake(Method(aabbStub, visitNotifyCollider));
	Fake(OverloadedMethod(aabbStub, visitNotifyCollider, void(Collider*)));
	Fake(OverloadedMethod(aabbStub, visitNotifyCollider, void(AABBCollider*)));
	Fake(OverloadedMethod(aabbStub, visitNotifyCollider, void(SphereCollider*)));
	Fake(Method(aabbStub, operation));
	Fake(Method(aabbStub, setCommand));
	

	AABBCollider& a = aabbStub.get();
	root->add(&a);
	root->operation();

	/*
	 * This will only trigger when child2->notify is called.
	 * This is because collision is only faked one way, aabbStub being asked
	 * if it collides with aabb
	*/
	Verify(OverloadedMethod(aabbStub,visitNotifyCollider,void(Collider*)).Using(aabb));
	Verify(Method(aabbStub, setParent).Using(root));
}

#include "geometry/moveable.hpp"
TEST_CASE("Collision volumes are transformed"){
	using namespace Geometry;
	using namespace Collision;
	Moveable root1;
	Moveable root2;

	glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
	float radius = 5.0f;
	SphereCollider sphere(center, radius);

	glm::vec3 min = glm::vec3(2.0f, 3.0f, 3.0f);
	glm::vec3 max = glm::vec3(4.0f, 4.0f, 4.0f);
	AABBCollider aabb(min, max);
	AABBCollider aabb2(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(3.0f,3.0f,3.0f));

	REQUIRE(sphere.visitCollide(&aabb));
	REQUIRE(aabb.visitCollide(&aabb2));

	root1.add(&sphere.getMoveable());
	root1.add(&aabb2);
	root1.translate(glm::vec3(10.0f,10.0f,10.0f));

	REQUIRE(!sphere.visitCollide(&aabb));
	REQUIRE(!aabb.visitCollide(&aabb2));

	root2.add(&aabb.getMoveable());
	root2.translate(glm::vec3(10.0f,10.0f,10.0f));

	REQUIRE(sphere.visitCollide(&aabb));
	REQUIRE(aabb.visitCollide(&aabb2));
	REQUIRE(aabb.visitCollide(&sphere));

	fmt::printf("Min %s\n", glm::to_string(aabb.getTransformedMin()));
	fmt::printf("Max %s\n", glm::to_string(aabb.getTransformedMax()));




}

TEST_CASE("Collision node test"){
	using namespace Collision;
	SECTION("Init node"){
		Node* root = new Node();

		REQUIRE(root != NULL);

		delete root;
	}
	SECTION("Add and remove to node"){
		Node* root = new Node();
		Node* child = new Node();

		root->add(child);
		REQUIRE(root->getChild(0) == child);
		REQUIRE(root->getChildCount() == 1);
		root->remove(0);
		REQUIRE(root->getChildCount() == 0);
		int index = root->insert(child);
		REQUIRE(index == 0);
		delete root;
		delete child;
	}
	SECTION("Set parent"){
		Node* root = new Node();
		Node* child = new Node();

		root->add(child);
		REQUIRE(child->getParent() == root);

	}

}
