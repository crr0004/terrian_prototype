#include "collision/simpleworld.hpp"
#include <fmt/format.h>

using namespace Collision;
void SimpleWorld::operation(){
	if(children.size() > 0){
		for(int i = 0; i < children.size(); i++){
			Collider* child = (Collider*)children.at(i);
			for(int j = i+1; j < children.size(); j++){
				Collider* child2 = (Collider*)children.at(j);
				if(child->visitCollide(child2)){
					child->notifyCollider(child2);
					child2->notifyCollider(child);
					child->getMoveable().translate(glm::vec3(0.1,0.0,0.0));
					child2->getMoveable().translate(glm::vec3(-0.1,0.0,0.0));
					//fmt::printf("Collision\n");
				}
			}
		}
	}
}

void SimpleWorld::add(INode* node){

}

void SimpleWorld::add(Collider* node){
	children.push_back(node);
}
