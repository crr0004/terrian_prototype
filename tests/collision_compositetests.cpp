#include <catch.hpp>
#include <fakeit.hpp>
#include "collision/node.hpp"

TEST_CASE("Collision Component Tests"){
	using namespace Collision;
	

	/*
	SimpleWorld *root = new SimpleWorld();
	AddToWorldCommand::SetRoot(root);

	float[] vertices = new float[9];
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

	AABBCollider triangleAABB = new AABBCollider(vertices);
	AddToWorldCommand addToWorld = new AddToWorldCommand(triangleAABB);
	*/
	
}

#include "collision/aabbcollider.hpp"
#include "collision/collider.hpp"
#include <glm/glm.hpp>
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
	Collider* sphere = new SphereCollider(center, radius);

	glm::vec3 min = glm::vec3(3.0f, 3.0f, 3.0f);
	glm::vec3 max = glm::vec3(4.0f, 4.0f, 4.0f);
	Collider* aabb = new AABBCollider(min, max);

	root->add(aabb);
	root->add(sphere);
	fakeit::Mock<AABBCollider> aabbStub;

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
