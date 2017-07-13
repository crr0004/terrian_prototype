cmake_minimum_required(VERSION 3.8)
set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "")
set_property( GLOBAL PROPERTY USE_FOLDERS ON)
project(TERRIAN_PROTOTYPE)

#Lua options
set(LUA_ANSI ON CACHE BOOL "")
set(LUA_BUILD_AS_DLL OFF CACHE BOOL "" )
set(LUA_BUILD_WLUA OFF CACHE BOOL "" )
set(LUA_BUILD_SHARED_LIBS OFF CACHE BOOL "" )
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" )
set(BUILD_TESTING OFF CACHE BOOL "" )
add_subdirectory(lua EXCLUDE_FROM_ALL)

#fmt
set(CMAKE_BUILD_TYPE RelWithDebugInfo)
set(FMT_USE_CPP11 OFF CACHE BOOL "")
add_subdirectory(fmt EXCLUDE_FROM_ALL)
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
	src/src/circle.cpp
	src/src/luae/scriptriangle.cpp
	src/src/addtodrawqueue.cpp
	src/src/luae/scriptmouse.cpp
	src/src/luae/scriptcollision.cpp
	src/src/node.cpp
	src/src/collision_simpleworld.cpp
	src/src/collision_aabbcollider.cpp
	src/src/collision_sphere.cpp
	src/src/geometry_moveable.cpp
	)
SET(Terrian_Prototype_Tests_src
	tests/Collision_planetest.cpp 
	tests/heightmaptests.cpp 
	tests/matrixstacksingletontests.cpp 
	tests/polygontests.cpp
	tests/luaescripttest.cpp
	tests/luaescriptmanagertest.cpp
	tests/luaetabletest.cpp
	tests/luaeutilitiestest.cpp
	tests/collision_compositetests.cpp
	tests/geometry_moveable.cpp
	)
SET(Terrian_Prototype_Headers
	src/headers/collision/AABB.hpp
	src/headers/collision/aabbcollider.hpp
	src/headers/collision/collider.hpp
	src/headers/collision/notification_command.hpp
	src/headers/collision/plane.hpp
	src/headers/collision/simpleworld.hpp
	src/headers/collision/spherecollider.hpp
	src/headers/geometry/moveable.hpp
	src/headers/geometry/point.hpp
	src/headers/luae/luae.hpp
	src/headers/luae/script.hpp
	src/headers/luae/scriptcollision.hpp
	src/headers/luae/scriptheightmap.hpp
	src/headers/luae/scriptmanager.hpp
	src/headers/luae/scriptmouse.hpp
	src/headers/luae/scriptriangle.hpp
	src/headers/luae/table.hpp
	src/headers/luae/Utilities.hpp
	src/headers/patterns/builder.hpp
	src/headers/patterns/command.hpp
	src/headers/addtodrawqueue.hpp
	src/headers/circle.hpp
	src/headers/gldebug.hpp
	src/headers/heightmap.hpp
	src/headers/INode.hpp
	src/headers/line.hpp
	src/headers/logiccontext.hpp
	src/headers/matrixstacksingleton.hpp
	src/headers/node.hpp
	src/headers/polygon.hpp
	src/headers/terrian_config.hpp
	src/headers/triangle.hpp
	src/headers/visualcontext.hpp
	src/headers/VisualServer.hpp
	)

add_executable(Terrian_Prototype src/main.cpp ${Terrian_Prototype_src} ${Terrian_Prototype_Headers})
add_executable(Terrian_Prototype_Tests tests/main.cpp ${Terrian_Prototype_src} ${Terrian_Prototype_Tests_src} ${Terrian_Prototype_Headers})
add_executable(StdLibScratch EXCLUDE_FROM_ALL src/stdlibscratch.cpp )
add_executable(LuaTests EXCLUDE_FROM_ALL src/luamain.cpp)
add_executable(GladScratch EXCLUDE_FROM_ALL src/gladscratch.cpp 	src/src/glad.c)
add_dependencies(Terrian_Prototype lua)
add_dependencies(LuaTests lua)

set_property(TARGET Terrian_Prototype_Tests PROPERTY CXX_STANDARD 11)
set_property(TARGET Terrian_Prototype PROPERTY CXX_STANDARD 98)
set_property(TARGET StdLibScratch PROPERTY CXX_STANDARD 11)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Terrian_Prototype)

#Project headers
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

#Add source group for IDEs
source_group(TREE "${PROJECT_SOURCE_DIR}/src/" FILES ${Terrian_Prototype_Headers})
source_group(TREE "${PROJECT_SOURCE_DIR}/src/src/" PREFIX "Source Files\\src" FILES ${Terrian_Prototype_src})
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Source Files" FILES ${Terrian_Prototype_Tests_src} tests/main.cpp)

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

include_directories(SYSTEM ${GLFWH})
#include_directories(${GLEWH})
include_directories(SYSTEM ${GLMH})
include_directories(SYSTEM ${FMT_HEADERS})
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
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W0")
	set_source_files_properties(
	  src/src/glad.c
	  PROPERTIES
	  COMPILE_FLAGS "-W0"
	)

	target_compile_options(Terrian_Prototype PRIVATE "/W4")

else()
	#Visual studio is a bit dumb and doesn't know what these mean
	target_compile_options(LuaTests PUBLIC -Og -g3)
	target_compile_options(Terrian_Prototype PUBLIC -O1 -g)
	target_compile_options(Terrian_Prototype_Tests PUBLIC -Og -ggdb)
	target_compile_options(liblua PUBLIC -Og -g3)
endif()

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
