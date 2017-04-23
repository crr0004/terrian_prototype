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

bool AABBCollider::visitCollide(Collider* node){
	return node->visitCollide(this);	
}

bool AABBCollider::visitCollide(AABBCollider* b){
	if (max[0] < b->min[0] || min[0] > b->max[0]) return false;
	if (max[1] < b->min[1] || min[1] > b->max[1]) return false;
	if (max[2] < b->min[2] || min[2] > b->max[2]) return false;
	// Overlapping on all axes means AABBs are intersecting
	return true;
}

bool AABBCollider::visitCollide(SphereCollider* sphere){
	return sphere->visitCollide(this);
}
void AABBCollider::visitNotifyCollider(Collider* collider){
	collider->visitNotifyCollider(this);
	if(command != NULL){
		command->execute();
	}
}
