#include "collision/spherecollider.hpp"
#include "collision/aabbcollider.hpp"
#include <cstddef>
using namespace Collision;

SphereCollider::SphereCollider(const glm::vec3& center, const float radius){
	this->center = glm::vec3(center);
	this->radius = radius;
	command = 0;
}

bool SphereCollider::visitCollide(Collider* node){
	return node->visitCollide(this);
}

bool SphereCollider::visitCollide(AABBCollider* aabb){
	glm::vec3 q;
	glm::vec3 center = getTransformedCenter();
	glm::vec3 min = aabb->getTransformedMin();
	glm::vec3 max = aabb->getTransformedMax();
	for (int i = 0; i < 3; i++) {
		float v = center[i];
		if (v < min[i]) v = min[i]; // v = max(v, b.min[i])
		if (v > max[i]) v = max[i]; // v = min(v, b.max[i])
		q[i] = v;
	}
	glm::vec3 v = q - center;
	return glm::dot(v,v) <= this->radius * this->radius;
}

bool SphereCollider::visitCollide(SphereCollider* sphere){
	return false;
}
void SphereCollider::visitNotifyCollider(Collider* collider){
	collider->visitNotifyCollider(this);
	if(command != NULL){
		command->execute();
	}
}

glm::vec3 SphereCollider::getTransformedCenter(){	
	return glm::vec3(moveable.getCulumativeMatrix() * glm::vec4(center, 1.0f)); 
}

Geometry::Moveable& SphereCollider::getMoveable(){
	return moveable;
}
