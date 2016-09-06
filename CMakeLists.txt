cmake_minimum_required(VERSION 3.6.1)
set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "")
project(TERRIAN_PROTOTYPE)

#Lua options
set(LUA_ANSI ON CACHE BOOL "")
set(LUA_BUILD_AS_DLL OFF CACHE BOOL "" )
set(LUA_BUILD_WLUA OFF CACHE BOOL "" )
set(LUA_BUILD_SHARED_LIBS OFF CACHE BOOL "" )
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" )
set(BUILD_TESTING OFF CACHE BOOL "" )
add_subdirectory(lua)

SET(Terrian_Prototype_src
	src/src/line.cpp 
	src/src/matrixstacksingleton.cpp 
	src/src/polygon.cpp 
	src/src/visualcontext.cpp 
	src/src/window.cpp
	src/src/luae/scriptheightmap.cpp
	src/src/heightmap.cpp 
	src/src/glad.c
	)
 SET(Terrian_Prototype_Tests_src
	tests/Collision_planetest.cpp 
	tests/heightmaptests.cpp 
	tests/matrixstacksingletontests.cpp 
	tests/polygontests.cpp
	)
	

add_executable(Terrian_Prototype src/main.cpp ${Terrian_Prototype_src})
ADD_EXECUTABLE(Terrian_Prototype_Tests tests/main.cpp ${Terrian_Prototype_src} ${Terrian_Prototype_Tests_src})
add_executable(LuaTests src/luamain.cpp)
add_executable(GladScratch src/gladscratch.cpp 	src/src/glad.c)
add_dependencies(Terrian_Prototype lua)
add_dependencies(LuaTests lua)

#Project headers
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

#Library locations (root directories)
set(GlfwLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.2.bin.WIN32/" CACHE PATH "GLFW Library Location")
#set(GlewLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glew-2.0.0/" CACHE PATH "Glew Library Location")
set(GlmLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glm/" CACHE PATH "GLM Library Location")

#Library file and header file locations for each library
if(MSVC)
	find_library(GLFW3 glfw3 PATHS "${GlfwLocation}" PATH_SUFFIXES "lib-vc2015")
endif()
if(MINGW)
	find_library(GLFW3 glfw3 PATHS "${GlfwLocation}" PATH_SUFFIXES "lib-mingw")
endif()
find_path(GLFWH GLFW/glfw3.h PATHS "${GlfwLocation}" PATH_SUFFIXES "include")

#find_library(GLEW glew32 PATHS "${GlewLocation}/" PATH_SUFFIXES "/lib/Release/x64/")
#find_path(GLEWH GL/glew.h PATHS "${GlewLocation}/" PATH_SUFFIXES "include")

find_path(GLMH glm/glm.hpp PATHS "${GlmLocation}" PATH_SUFFIXES "include")

include_directories(${GLFWH})
#include_directories(${GLEWH})
include_directories(${GLMH})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Terrian_Prototype OpenGL32 glu32 ${GLFW3} liblua)
target_link_libraries(GladScratch OpenGL32 glu32 ${GLFW3} liblua)
target_link_libraries(LuaTests liblua)
TARGET_LINK_LIBRARIES(Terrian_Prototype_Tests OpenGL32 glu32 ${GLFW3} liblua)

#Compiler options for Visual Studios
if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
endif()

set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders/" CACHE PATH "Directory containing shaders")
set(SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lua_scripts/" CACHE PATH "Directory containing lua scripts")
#file(COPY ${GlewLocation}/bin/Release/x64/glew32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY lua/src/lua.h lua/src/lualib.h lua/src/lauxlib.h lua/src/lua.hpp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/lua/)

#Output the configuration header
configure_file(terrian_config.h.in terrian_config.h @ONLY)
configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/lua/src/luaconf.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/lua/luaconf.h )
set(HEADER_DIRS "")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
	string(APPEND HEADER_DIRS "${dir},")
endforeach()
string(REGEX REPLACE ",$" "" HEADER_DIRS ${HEADER_DIRS})
message(STATUS ${HEADER_DIRS})
set(HEADER_DIRS_STRING ${HEADER_DIRS} CACHE STRING "List of included directories")
