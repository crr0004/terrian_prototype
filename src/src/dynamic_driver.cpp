#include "dynamics/dynamic_driver.hpp"

using namespace Dynamics;
DynamicDriver::DynamicDriver(){

	clock_gettime(CLOCK_MONOTONIC, &currentTime);
    accumulator = 0.0;
}

void DynamicDriver::operation(){
    t = 0.0;
    dt = 0.01;


	clock_gettime(CLOCK_MONOTONIC, &newTime);
	frameTime = (newTime.tv_sec + (newTime.tv_nsec/1.0e9)) - (currentTime.tv_sec + (currentTime.tv_nsec/1.0e9));
	//	fmt::printf("frame time in seconds %f\n", frameTime);
	if ( frameTime > 0.25 )
		frameTime = 0.25;

	clock_gettime(CLOCK_MONOTONIC, &currentTime);

	accumulator += frameTime;

	while ( accumulator >= dt )
	{
		//	previousState = currentState;
		//	integrate( currentState, t, dt );
		for(int i = 0; i < children.size(); i++){
			children.at(i)->operation();
			children.at(i)->visit((INode*)this);
		}
		t += dt;
		accumulator -= dt;
	}
}

void DynamicDriver::add(INode* node){
	children.push_back(node);
	node->setParent(this);
}

void DynamicDriver::add(DynamicNode* node){
	children.push_back(node);
	node->setParent(this);
}

int DynamicDriver::visit(DynamicNode* node){
	node->step(this->t, this->dt);

	return 0;
}

int DynamicDriver::visit(INode*){

	return 0;

}
