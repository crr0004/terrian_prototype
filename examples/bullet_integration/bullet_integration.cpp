#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <lua/lua.hpp>
#include <vector>
#include <fmt/format.h>
#include <btBulletDynamicsCommon.h>
#include <time.h>
#include <chrono>

#include "terrian_config.hpp"
#include "matrixstacksingleton.hpp"
#include "polygon.hpp"
#include "logiccontext.hpp"
#include "visualcontext.hpp"
#include "heightmap.hpp"
#include "line.hpp"
#include "triangle.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "addtodrawqueue.hpp"
#include "luae/script.hpp"
#include "luae/scriptmanager.hpp"
#include "luae/scriptheightmap.hpp"
#include "luae/scriptriangle.hpp"
#include "luae/scriptmouse.hpp"
#include "print_node.hpp"
#include "bullet_node.hpp"
#include "bullet_contactmanifold_node.hpp"

#include "collision/simpleworld.hpp"
#include "collision/spherecollider.hpp"

//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second

static struct LogicContext logicContext;
static glm::vec3 ray_world;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	glm::vec3 up = glm::vec3(glm::vec4(0.0, 1.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 down = glm::vec3(glm::vec4(0.0, -1.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 left = glm::vec3(glm::vec4(-1.0, 0.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 right = glm::vec3(glm::vec4(1.0, 0.0, 0.0, 1.0) * logicContext.modelview);
	glm::vec3 back = glm::vec3(glm::vec4(0.0, 0.0, -1.0, 1.0) * logicContext.modelview);
	glm::vec3 forward = glm::vec3(glm::vec4(0.0, 0.0, 1.0, 1.0) * logicContext.modelview);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		printf("Triangle 1 Model Matrix: %s\n", glm::to_string(logicContext.modelview).c_str());
	}
	if(key == GLFW_KEY_R && action == GLFW_RELEASE){
		logicContext.modelview = glm::mat4();

	}
	if(key == GLFW_KEY_LEFT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, up);
	}
	else if(key == GLFW_KEY_RIGHT && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, down);
	}
	else if(key == GLFW_KEY_LEFT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, left * 0.1f);
	}
	else if(key == GLFW_KEY_RIGHT && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, right * 0.1f);
	}
	if(key == GLFW_KEY_UP && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, up * 0.1f);
	}
	else if(key == GLFW_KEY_DOWN && mods == 0){
		logicContext.modelview = glm::translate(logicContext.modelview, down * 0.1f);
	}
	else if(key == GLFW_KEY_UP && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, left);
	}
	else if(key == GLFW_KEY_DOWN && mods == GLFW_MOD_SHIFT){
		logicContext.modelview = glm::rotate(logicContext.modelview, 0.1f, right);

	}else if(key == GLFW_KEY_UP && mods == GLFW_MOD_CONTROL){
		logicContext.modelview = glm::translate(logicContext.modelview, back * 0.1f);
	}else if(key == GLFW_KEY_DOWN && mods == GLFW_MOD_CONTROL){
		logicContext.modelview = glm::translate(logicContext.modelview, forward * 0.1f);
	}
}
static void calcWorldPickRay(GLFWwindow *window){
	//Build ray from mouse
	double mouseX;
	double mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	glm::vec4 ray_clip = glm::vec4((2.0f * mouseX) / VisualContext::width - 1.0f, 1.0f - (2.0f * mouseY) / VisualContext::height, -1.0f, 1.0f);

	glm::vec4 ray_eye = glm::inverse(VisualContext::projection_matrix) * ray_clip;
	ray_eye.z = -1.0f;
	ray_eye.w = 1.0f;

	ray_world = glm::vec3(glm::inverse(logicContext.modelview) * ray_eye);
	//		ray_world = glm::normalize(ray_world);

}

int main(void) {
	//disable stdout buffering
	setbuf(stdout, NULL);

	//Setup for windows
	GLFWwindow *window = VisualContext::CreateGLFWWindow(key_callback);
	GLuint shader_program = VisualContext::make_shader_program(concat(xstr(SHADERS_DIR), "/shader.vert"), concat(xstr(SHADERS_DIR), "/shader.frag"));
	glUseProgram(shader_program);
	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");
	GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
	GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");

	/* Compute the projection matrix */
	VisualContext::projection_matrix = glm::perspective(VisualContext::view_angle, VisualContext::aspect_ratio, VisualContext::z_near, VisualContext::z_far);
	logicContext.uloc_modelview = uloc_modelview;

	/* Set the camera position  */
	logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -20.0f));
	logicContext.modelview = glm::rotate(logicContext.modelview, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
	glViewport(0,0,VisualContext::width, VisualContext::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//END Setup for windows


	//Create a draw queue
	std::vector<Geometry::Polygon*> drawQueue;
	//Draw queue gets added to a command so other parts of code can easily add
	//to queue
	AddToDrawQueueCommand::SetQueue(&drawQueue);



///-----includes_end-----

	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	btCollisionWorld* collisionWorld = new btCollisionWorld(dispatcher, overlappingPairCache, collisionConfiguration);

	///-----initialization_end-----

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	///create a few basic rigid bodies

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5
		//this creates a box with half lengths of 10
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(10.), btScalar(2.5), btScalar(10.)));

		collisionShapes.push_back(groundShape);
		btCollisionObject* ground = new btCollisionObject();
		ground->getWorldTransform().setOrigin(btVector3(-5, -5, 0));

		ground->setCollisionShape(groundShape);

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);
		btCollisionObject* sphere = new btCollisionObject();
		sphere->getWorldTransform().setOrigin(btVector3(0,0,0));
		sphere->setCollisionShape(colShape);

		collisionWorld->addCollisionObject(ground);
		collisionWorld->addCollisionObject(sphere);

	Geometry::Rectangle rectangle;
	//Our rectangle doesn't use half lengths at the moment
	rectangle.setLengths(20,5);

	rectangle.setLogicContext(&logicContext);
	rectangle.setShaderLocations(vertShaderLocation);
	rectangle.buildStatic();

	drawQueue.push_back(&rectangle);

	btTransform rectTrans = ground->getWorldTransform();
	btVector3& rectOrigin = rectTrans.getOrigin();
	//Minus half lengths of bulletbox because our objects origins are at
	//bottom left, not middle of object
	rectangle.getMoveable().setPos(glm::vec3(
				rectOrigin.getX()-10,rectOrigin.getY()-2.5,rectOrigin.getZ()));

	Geometry::Circle circle;
	circle.setLogicContext(&logicContext);
	circle.setShaderLocations(vertShaderLocation);
	circle.buildStatic();
	circle.getMoveable().setPos(glm::vec3(0.0,12.0,0.0));


	drawQueue.push_back(&circle);

	/// Do some simulation
	
	//Enables antialiasing
	glEnable(GL_MULTISAMPLE);
    double t = 0.0;
    double dt = 0.01;

	std::chrono::time_point<std::chrono::steady_clock> currentTime, newtime;
	currentTime = std::chrono::steady_clock::now();
	//double now_mili = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	//clock_gettime(CLOCK_MONOTONIC, &currentTime);
    double accumulator = 0.0;

	BulletNode sampleNode1(1);
	BulletNode sampleNode2(2);
	sphere->setUserPointer(&sampleNode1);
	ground->setUserPointer(&sampleNode2);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));

	///-----stepsimulation_end-----
		//clock_gettime(CLOCK_MONOTONIC, &newTime);
		newtime = std::chrono::steady_clock::now();
		//double frameTime = (newTime.tv_sec + (newTime.tv_nsec/1.0e9)) - (currentTime.tv_sec + (currentTime.tv_nsec/1.0e9));
		double frameTime = std::chrono::duration_cast<std::chrono::seconds>(newtime - currentTime).count();
		//	fmt::printf("frame time in seconds %f\n", frameTime);
		//frameTime = 0;
		if ( frameTime > 0.25 )
			frameTime = 0.25;

		//clock_gettime(CLOCK_MONOTONIC, &currentTime);

		accumulator += frameTime;

		while ( accumulator >= dt )
		{
		//	previousState = currentState;
		//	integrate( currentState, t, dt );
			//fmt::printf("-9.8*dt = %f\n", -9.8*dt);
			circle.getMoveable().translate(glm::vec3(0.0, -4.8*dt, 0.0));
			
			glm::vec3 circlePos = circle.getMoveable().getPosAsVec3();
			//fmt::printf("Circle pos %f,%f,%f\n", circlePos.x, circlePos.y, circlePos.z);
			t += dt;
			accumulator -= dt;
		}

		//circle.getMoveable().setPos(glm::vec3( sphereOrigin.getX(),sphereOrigin.getY(),sphereOrigin.getZ()));
		//btTransform sphereTrans = sphere->getWorldTransform();
		//btVector3& sphereOrigin = sphereTrans.getOrigin();
		glm::vec3 circlePos = circle.getMoveable().getPosAsVec3();
		sphere->getWorldTransform().setOrigin(btVector3(circlePos.x, circlePos.y, circlePos.z));
		const double alpha = accumulator / dt;
	
		collisionWorld->performDiscreteCollisionDetection();

		int numManifolds = collisionWorld->getDispatcher()->getNumManifolds();

		for (int i = 0; i < numManifolds; i++) {
			btPersistentManifold* contactManifold = collisionWorld->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
			const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
			if(obA->getUserPointer() != nullptr && obB->getUserPointer() != nullptr){
				BulletContactManifoldNode manifoldNode(contactManifold);
				BulletNode* nodeA = static_cast<BulletNode*>(obA->getUserPointer());
				BulletNode* nodeB = static_cast<BulletNode*>(obB->getUserPointer());
				//Visit nodeA and B so we can tell them we have a
				//manifoldNode class.
				manifoldNode.visit(nodeA);
				manifoldNode.visit(nodeB);
			}
			contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
			int numContacts = contactManifold->getNumContacts();
			//For each contact point in that manifold
			for (int j = 0; j < numContacts; j++) {
				//Get the contact information
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				btVector3 ptA = pt.getPositionWorldOnA();
				btVector3 ptB = pt.getPositionWorldOnB();
				double ptdist = pt.getDistance();
			}
		}

		for(std::vector<Geometry::Polygon*>::iterator drawHost = drawQueue.begin();
				drawHost != drawQueue.end();
				drawHost++){
			glDisable(GL_CULL_FACE);
			/**
			 * TODO This is okay for now, however the logicContext will become
			 * the shader from a shader manager/factory 
			 * so each object should set it, itself.
			 * (*drawHost)->setLogicContext(&logicContext);
			 */
			(*drawHost)->setLogicContext(&logicContext);

			(*drawHost)->update();
			(*drawHost)->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	MatrixStackSingleton::Destroy();
	//cleanup in the reverse order of creation/initialization

	/*
	///-----cleanup_start-----

	//remove the rigidbodies from the dynamics world and delete them
	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
collisionShapes.clear();	
*/

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;
}
