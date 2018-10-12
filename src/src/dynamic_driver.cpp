#include "dynamics/dynamic_driver.hpp"

using namespace Dynamics;
DynamicDriver::DynamicDriver(){

	
	currentTime = std::chrono::steady_clock::now();
	//clock_gettime(CLOCK_MONOTONIC, &currentTime);
	
	//double frameTime = (newTime.tv_sec + (newTime.tv_nsec/1.0e9)) - (currentTime.tv_sec + (currentTime.tv_nsec/1.0e9));
	
    accumulator = 0.0;
}

void DynamicDriver::operation(){
    t = 0.0;
    dt = 0.01;


	//clock_gettime(CLOCK_MONOTONIC, &newTime);
	newtime = std::chrono::steady_clock::now();
	//frameTime = (newTime.tv_sec + (newTime.tv_nsec/1.0e9)) - (currentTime.tv_sec + (currentTime.tv_nsec/1.0e9));
	frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(newtime - currentTime).count();
	//	fmt::printf("frame time in seconds %f\n", frameTime);
	if ( frameTime > 0.25 )
		frameTime = 0.25;

	//clock_gettime(CLOCK_MONOTONIC, &currentTime);
	currentTime = std::chrono::steady_clock::now();

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
