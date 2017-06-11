#include "collision/aabbcollider.hpp"
#include "collision/spherecollider.hpp"
#include <cstddef>
#include <glm/glm.hpp>
using namespace Collision;
AABBCollider::AABBCollider(const glm::vec3& min, const glm::vec3& max){
	this->min = glm::vec3(min);
	this->max = glm::vec3(max);
	command = 0;
}

bool AABBCollider::collides(const AABBCollider& b){
	if (max[0] < b.min[0] || min[0] > b.max[0]) return false;
	if (max[1] < b.min[1] || min[1] > b.max[1]) return false;
	if (max[2] < b.min[2] || min[2] > b.max[2]) return false;
	// Overlapping on all axes means AABBs are intersecting
	return true;
}

Geometry::Moveable& AABBCollider::getMoveable(){
	return moveable;
}
glm::vec3 AABBCollider::getTransformedMin(){
	return glm::vec3(moveable.getCulumativeMatrix() * glm::vec4(min, 1.0f));
}

glm::vec3 AABBCollider::getTransformedMax(){
	return glm::vec3(moveable.getCulumativeMatrix() * glm::vec4(max, 1.0f));
}

bool AABBCollider::visitCollide(Collider* node){
	return node->visitCollide(this);	
}


bool AABBCollider::visitCollide(AABBCollider* b){
	glm::vec3 min = getTransformedMin();
	glm::vec3 max = getTransformedMax();
	glm::vec3 bmin = b->getTransformedMin();
	glm::vec3 bmax = b->getTransformedMax();
	if (max[0] < bmin[0] || min[0] > bmax[0]) return false;
	if (max[1] < bmin[1] || min[1] > bmax[1]) return false;
	if (max[2] < bmin[2] || min[2] > bmax[2]) return false;
	// Overlapping on all axes means AABBs are intersecting
	return true;
}

bool AABBCollider::visitCollide(SphereCollider* sphere){
	return sphere->visitCollide(this);
}
void AABBCollider::notifyCollider(Collider* collider){
}
