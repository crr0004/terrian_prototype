cmake_minimum_required(VERSION 3.6.1)
project(TERRIAN_PROTOTYPE)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

add_executable(Terrian_Prototype src/main.cpp src/heightmap.cpp src/line.cpp src/matrixstacksingleton.cpp src/polygon.cpp src/visualcontext.cpp src/window.cpp)
target_link_libraries(Terrian_Prototype OpenGL32)

/*cmake_minimum_required(VERSION 3.6)
project(BUILD_TEST)

add_executable(Build_Test main.cpp)
set(GlfwLocation "$ENV{USERPROFILE}/dev/Source/glfw-3.2" CACHE PATH "GLFW Library Location")
include_directories(PUBLIC "${GlfwLocation}/" "${GlfwLocation}/../include")
message(STATUS ${INCLUDE_DIRECTORIES})
target_link_libraries(Build_Test OpenGL32 glu32 glfw3)
*/