#include "collision/simpleworld.hpp"

using namespace Collision;
void SimpleWorld::operation(){
	if(children.size() > 0){
		for(int i = 0; i < children.size(); i++){
			Collider* child = (Collider*)children.at(i);
			for(int j = 0; j < children.size(); j++){
				if(j != i){
					Collider* child2 = (Collider*)children.at(j);
					if(child->visitCollide(child2)){
						child->visitNotifyCollider(child2);
						child2->visitNotifyCollider(child);
					}
				}
			}
		}
	}
}

void SimpleWorld::add(INode* node){

}

void SimpleWorld::add(Collider* node){
	children.push_back(node);
	node->setParent(this);
}
