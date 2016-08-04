cmake_minimum_required(VERSION 3.6.1)
project(TERRIAN_PROTOTYPE)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

add_executable(Terrian_Prototype src/main.cpp src/heightmap.cpp src/line.cpp src/matrixstacksingleton.cpp src/polygon.cpp src/visualcontext.cpp src/window.cpp)
target_link_libraries(Terrian_Prototype OpenGL32)

cmake_minimum_required(VERSION 3.6)
project(BUILD_TEST)

add_executable(Build_Test main.cpp)
set(GlfwLocation "$ENV{USERPROFILE}/dev/Source/glfw-3.2/" CACHE PATH "GLFW Library Location")
set(GlewLocation "$ENV{USERPROFILE}/dev/Source/glew-2.0.0/" CACHE PATH "Glew Library Location")
set(GlmLocation "$ENV{USERPROFILE}/dev/Source/glm/" CACHE PATH "GLM Library Location")

find_library(GLFW3 glfw3 PATHS "${GlfwLocation}" PATH_SUFFIXES "lib-vc2015")
find_path(GLFWH GLFW/glfw3.h PATHS "${GlfwLocation}" PATH_SUFFIXES "include")

find_library(GLEW glew PATHS "${GlmLocation}" PATH_SUFFIXES "lib/Release/Win32" "lib/Release/x64" "bin/Release/Win32" "bin/Release/x64")
find_path(GLEWH GL/glew.h PATHS "${GlewLocation}" PATH_SUFFIXES "include")
message(STATUS ${GLEW})

include_directories(${GLFWH})

target_link_libraries(Build_Test OpenGL32 glu32 ${GLFW3})
