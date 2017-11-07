#include "polygon.hpp"
#include <catch.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <iostream>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"
#include "visualcontext.hpp"
#include "terrian_config.hpp"
#include "dynamics/dynamic_node.hpp"
//For stringifying preprocessor values
#define xstr(s) str(s)
     #define str(s) #s
#define concat(first, second) first second

using namespace Dynamics;
TEST_CASE("Dynamics use"){

	DyanamicNode dynamicNode();

}
