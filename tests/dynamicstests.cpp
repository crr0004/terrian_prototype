#include <catch.hpp>
#include <fakeit.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <fmt/format.h>
#include <iostream>
#include <chrono>
#include <thread>
#include "terrian_config.hpp"

#include "dynamics/dynamic_node.hpp"
#include "dynamics/dynamic_driver.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second

using namespace Dynamics;
using namespace fakeit;
TEST_CASE("DynamicDriver tests", "[current]"){
	/*
	DynamicDriver driver();
	//This will ensure our driver is giving off correct timesteps
	Mock<DyanamicNode> mockPrintDynamicNode;

	driver.add(mockPrintDynamicNode);
	*/

	SECTION("Visit fires correctly"){
		//Make sure when calling visit on DynamicNode that it calls the
		//caller with itself correctly. In this case, DynamicDriver gets
		//called with DynamicNode.
		Mock<DynamicDriver> mockDriver;
		DynamicNode node;
		Fake(OverloadedMethod(mockDriver, visit, int(DynamicNode*)));
		INode* driverNode = (INode*)&mockDriver.get();
		node.visit(driverNode);
		Verify(OverloadedMethod(mockDriver, visit, int(DynamicNode*)).Using(&node));

	}
	SECTION("Operation calls on child nodes"){
		Mock<DynamicNode> mockNode;
		DynamicNode node2;
		DynamicDriver driver;
		Fake(OverloadedMethod(mockNode, visit, int(INode*)));
		Fake(Method(mockNode, setParent));
		Fake(Method(mockNode, operation));

		DynamicNode* node = (DynamicNode*)&mockNode.get();
		driver.add(node);
		driver.add(&node2);
		driver.operation();
		//We sleep so operation will see some sort of time pass
		//Idealy this should be dependancy injected but meh
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		driver.operation();

		Verify(OverloadedMethod(mockNode, visit, int(INode*)).Using(&driver));

	}
	SECTION("Visit call to DynamicNode result in a step call"){
		Mock<DynamicNode> mockNode;
		DynamicDriver driver;
		Fake(OverloadedMethod(mockNode, visit, int(INode*)));
		Fake(Method(mockNode, step));

		DynamicNode* node = (DynamicNode*)&mockNode.get();
		driver.visit(node);

		Verify(Method(mockNode, step));
	}
	SECTION("Times are correct"){
		double t = 0.0;
		double dt = 0.01;

		struct timespec currentTime, newTime;	
		clock_gettime(CLOCK_MONOTONIC, &currentTime);
		//Only need this if we're trying to find a guess for frametime
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));

		double accumulator = 0.0;
		clock_gettime(CLOCK_MONOTONIC, &newTime);
		double frameTime = (newTime.tv_sec + (newTime.tv_nsec/1.0e9)) - (currentTime.tv_sec + (currentTime.tv_nsec/1.0e9));
		frameTime = 0.02; //fix the frameTime in place for testing reasons. Remove this when using in non-test code
		//	fmt::printf("frame time in seconds %f\n", frameTime);
		if ( frameTime > 0.25 )
			frameTime = 0.25;

		clock_gettime(CLOCK_MONOTONIC, &currentTime);

		accumulator += frameTime;
		t += dt;

		accumulator -= dt;
		REQUIRE(t == 0.01);
		REQUIRE(accumulator == 0.01);
		t += dt;
		accumulator -= dt;
		REQUIRE(t == 0.02);
		REQUIRE(accumulator == 0);

		const double alpha = accumulator / dt;
	}

}
TEST_CASE("Dynamics use"){

	DynamicNode dynamicNode();

}
