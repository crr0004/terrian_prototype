cmake_minimum_required(VERSION 3.4)
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

#fmt
set(CMAKE_BUILD_TYPE RelWithDebugInfo)
set(FMT_USE_CPP11 OFF CACHE BOOL "")
add_subdirectory(fmt)
#Revert options for fmt
set(CMAKE_BUILD_TYPE Debug)

SET(Terrian_Prototype_src
	src/src/line.cpp 
	src/src/matrixstacksingleton.cpp 
	src/src/polygon.cpp 
	src/src/visualcontext.cpp 
	src/src/luae/scriptheightmap.cpp
	src/src/heightmap.cpp 
	src/src/glad.c
	src/src/luae/script.cpp
	src/src/luae/scriptmanager.cpp
	src/src/luae/table.cpp
	src/src/triangle.cpp
	src/src/luae/scriptriangle.cpp
	src/src/renderfactory.cpp
	src/src/vertexattributebuilder.cpp
	src/src/vertexattributebuilt.cpp
	src/src/arraybufferbuilder.cpp
	src/src/arraybufferbuilt.cpp
	)
SET(Terrian_Prototype_Tests_src
	tests/Collision_planetest.cpp 
	tests/heightmaptests.cpp 
	tests/matrixstacksingletontests.cpp 
	tests/polygontests.cpp
	tests/luaescripttest.cpp
	tests/luaescriptmanagertest.cpp
	tests/luaetabletest.cpp
	tests/renderfactorytests.cpp
	)
	

add_executable(Terrian_Prototype src/main.cpp ${Terrian_Prototype_src})
add_executable(Terrian_Prototype_Tests tests/main.cpp ${Terrian_Prototype_src} ${Terrian_Prototype_Tests_src})
add_executable(StdLibScratch src/stdlibscratch.cpp)
add_executable(LuaTests src/luamain.cpp)
add_executable(GladScratch src/gladscratch.cpp 	src/src/glad.c)
add_dependencies(Terrian_Prototype lua)
add_dependencies(LuaTests lua)

set_property(TARGET Terrian_Prototype_Tests PROPERTY CXX_STANDARD 11)
set_property(TARGET Terrian_Prototype PROPERTY CXX_STANDARD 98)
set_property(TARGET StdLibScratch PROPERTY CXX_STANDARD 11)

#Project headers
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

#Library locations (root directories)
set(GlfwLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.2.1.bin.WIN64/" CACHE PATH "GLFW Library Location")
set(GlmLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glm/" CACHE PATH "GLM Library Location")

#Library file and header file locations for each library
message(STATUS ${MSVC})
if(MSVC)

	find_library(GLFW3 glfw3 PATHS "${GlfwLocation}" PATH_SUFFIXES "lib-vc2015")
elseif(MINGW)
	find_library(GLFW3 glfw3 PATHS "${GlfwLocation}" PATH_SUFFIXES "lib-mingw")
else()
	find_library(GLFW3 glfw PATHS "${GlfwLocation}")
endif()

find_path(GLFWH GLFW/glfw3.h PATHS "${GlfwLocation}" PATH_SUFFIXES "include")

find_path(GLMH glm/glm.hpp PATHS "${GlmLocation}" PATH_SUFFIXES "include")

include_directories(${GLFWH})
#include_directories(${GLEWH})
include_directories(${GLMH})
include_directories(${FMT_HEADERS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
	set(WIN_LIBS OpenGL32 glu32)
	target_link_libraries(Terrian_Prototype ${WIN_LIBS})
	target_link_libraries(GladScratch ${WIN_LIBS})
	target_link_libraries(Terrian_Prototype_Tests ${WIN_LIBS})

else()
	set(UNIX_LIBS GLU GLU)
	target_link_libraries(Terrian_Prototype ${UNIX_LIBS})
	target_link_libraries(GladScratch ${UNIX_LIBS})
	target_link_libraries(Terrian_Prototype_Tests ${UNIX_LIBS})

endif()
set(LIBS ${GLFW3} liblua fmt)
target_link_libraries(Terrian_Prototype ${LIBS})
target_link_libraries(GladScratch ${LIBS})
target_link_libraries(LuaTests liblua)
target_link_libraries(Terrian_Prototype_Tests ${LIBS})
target_link_libraries(StdLibScratch fmt)

#Compiler options for Visual Studios
if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
endif()
target_compile_options(LuaTests PUBLIC -Og -g3)
#target_compile_options(Terrian_Prototype_Tests PUBLIC -Og -g3)
target_compile_options(liblua PUBLIC -Og -g3)

set(SHADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders/" CACHE PATH "Directory containing shaders")
set(SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lua_scripts/" CACHE PATH "Directory containing lua scripts")
file(COPY lua/src/lua.h lua/src/lualib.h lua/src/lauxlib.h lua/src/lua.hpp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/lua/)

#Output the configuration header
configure_file(terrian_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/headers/terrian_config.hpp @ONLY)
configure_file ( ${CMAKE_CURRENT_SOURCE_DIR}/lua/src/luaconf.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/lua/luaconf.h )
set(HEADER_DIRS "")
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
	string(APPEND HEADER_DIRS "${dir},")
endforeach()
string(REGEX REPLACE ",$" "" HEADER_DIRS ${HEADER_DIRS})
message(STATUS ${HEADER_DIRS})
set(HEADER_DIRS_STRING ${HEADER_DIRS} CACHE STRING "List of included directories")
