cmake_minimum_required(VERSION 3.6.1)
set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "")
project(TERRIAN_PROTOTYPE)

add_subdirectory(lua)
set(LUA_ANSI ON CACHE BOOL "" FORCE)
set(LUA_BUILD_AS_DLL OFF CACHE BOOL "" FORCE)
set(LUA_BUILD_WLUA OFF CACHE BOOL "" FORCE)
set(LUA_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_executable(Terrian_Prototype src/main.cpp src/src/heightmap.cpp src/src/line.cpp src/src/matrixstacksingleton.cpp src/src/polygon.cpp src/src/visualcontext.cpp src/src/window.cpp)
add_dependencies(Terrian_Prototype lua)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")
link_directories(Terrian_Prototype lua)

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

target_link_libraries(Terrian_Prototype OpenGL32 ${GLEW} glu32 ${GLFW3} liblua_static)
file(COPY lua/src/lua.h lua/src/lualib.h lua/src/lauxlib.h lua/etc/lua.hpp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/lua/)
