cmake_minimum_required(VERSION 3.6.1)
project(TERRIAN_PROTOTYPE)

add_executable(Terrian_Prototype src/main.cpp src/heightmap.cpp src/line.cpp src/matrixstacksingleton.cpp src/polygon.cpp src/visualcontext.cpp src/window.cpp)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

set(GlfwLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.2.bin.WIN64/" CACHE PATH "GLFW Library Location")
set(GlewLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glew-2.0.0/" CACHE PATH "Glew Library Location")
set(GlmLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glm/" CACHE PATH "GLM Library Location")

find_library(GLFW3 glfw3 PATHS "${GlfwLocation}" PATH_SUFFIXES "lib-vc2015")
find_path(GLFWH GLFW/glfw3.h PATHS "${GlfwLocation}" PATH_SUFFIXES "include")

find_library(GLEW glew32 PATHS "${GlewLocation}/" PATH_SUFFIXES "/lib/Release/x64/")
find_path(GLEWH GL/glew.h PATHS "${GlewLocation}/" PATH_SUFFIXES "include")

find_path(GLMH glm/glm.hpp PATHS "${GlmLocation}" PATH_SUFFIXES "include")

include_directories(${GLFWH})
include_directories(${GLEWH})
include_directories(${GLMH})

target_link_libraries(Terrian_Prototype OpenGL32 ${GLEW} glu32 ${GLFW3} )
