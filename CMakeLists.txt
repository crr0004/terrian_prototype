cmake_minimum_required(VERSION 3.6)
set(CMAKE_INSTALL_PREFIX "install" CACHE PATH "")
set_property( GLOBAL PROPERTY USE_FOLDERS ON)
project(Jelly_Engine)

#Lua options
set(LUA_ANSI ON CACHE BOOL "")
set(LUA_BUILD_AS_DLL OFF CACHE BOOL "" )
set(LUA_BUILD_WLUA OFF CACHE BOOL "" )
set(LUA_BUILD_SHARED_LIBS OFF CACHE BOOL "" )
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" )
set(BUILD_TESTING OFF CACHE BOOL "" )
set(LUA_USE_READLINE OFF CACHE BOOL "")
set(LUA_USE_CURSES OFF CACHE BOOL "")
add_subdirectory(lua EXCLUDE_FROM_ALL)

#fmt
set(CMAKE_BUILD_TYPE RelWithDebugInfo)
set(FMT_USE_CPP11 OFF CACHE BOOL "")
add_subdirectory(fmt EXCLUDE_FROM_ALL)
#Revert options for fmt
set(CMAKE_BUILD_TYPE Debug)

#Project headers
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}/src/headers")

find_package(PkgConfig REQUIRED)
pkg_check_modules(BULLET REQUIRED bullet)


#Library locations (root directories)
set(GlfwLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.2.1.bin.WIN64/" CACHE PATH "GLFW Library Location")
set(GlmLocation "${CMAKE_CURRENT_SOURCE_DIR}/../glm/" CACHE PATH "GLM Library Location")

#Library file and header file locations for each library
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
include_directories(${BULLET_INCLUDE_DIRS})

set(LIBS ${GLFW3} liblua fmt ${BULLET_LIBRARIES})

if(WIN32)
	set(LIBS ${LIBS} OpenGL32 glu32)
else()
	set(LIBS ${LIBS} GLU GLU)
endif()



#Compiler options for Visual Studios
if(MSVC)

else()
	#Visual studio is a bit dumb and doesn't know what these mean
	#target_compile_options(LuaTests PUBLIC -Og -g3)

	#target_compile_options(Terrian_Prototype_Tests PUBLIC -Og -ggdb)
	#target_compile_options(liblua PUBLIC -Og -g3)
endif()


ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)
ADD_SUBDIRECTORY(examples)

#add_executable(StdLibScratch EXCLUDE_FROM_ALL src/stdlibscratch.cpp )
#add_executable(LuaTests EXCLUDE_FROM_ALL src/luamain.cpp)
#add_executable(GladScratch EXCLUDE_FROM_ALL src/gladscratch.cpp src/src/glad.c)

#target_link_libraries(GladScratch ${LIBS})
#target_link_libraries(LuaTests liblua)
#target_link_libraries(StdLibScratch fmt)

#add_dependencies(LuaTests lua)



set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)

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
