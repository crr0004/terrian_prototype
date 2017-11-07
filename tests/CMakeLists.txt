cmake_minimum_required(VERSION 3.6)

SET(TESTS_SRC
	${PROJECT_SOURCE_DIR}/tests/Collision_planetest.cpp 
	${PROJECT_SOURCE_DIR}/tests/heightmaptests.cpp 
	${PROJECT_SOURCE_DIR}/tests/matrixstacksingletontests.cpp 
	${PROJECT_SOURCE_DIR}/tests/polygontests.cpp
	${PROJECT_SOURCE_DIR}/tests/luaescripttest.cpp
	${PROJECT_SOURCE_DIR}/tests/luaescriptmanagertest.cpp
	${PROJECT_SOURCE_DIR}/tests/luaetabletest.cpp
	${PROJECT_SOURCE_DIR}/tests/luaeutilitiestest.cpp
	${PROJECT_SOURCE_DIR}/tests/collision_compositetests.cpp
	${PROJECT_SOURCE_DIR}/tests/geometry_moveable.cpp
	${PROJECT_SOURCE_DIR}/tests/dynamicstests.cpp
)

SET(JELLY_ENGINE_TESTS ${TESTS_SRC} PARENT_SCOPE)

if(${CMAKE_VERSION} VERSION_GREATER "3.8.2")
source_group(TREE "${PROJECT_SOURCE_DIR}/" PREFIX "Source Files" FILES ${TESTS_SRC} main.cpp)

endif()

add_executable(Tests main.cpp ${MAIN_SRC} ${TESTS_SRC} ${MAIN_HEADERS})
target_link_libraries(Tests ${LIBS})
set_property(TARGET Tests PROPERTY CXX_STANDARD 11)

#Compiler options for Visual Studios
if(MSVC)

else()
	#Visual studio is a bit dumb and doesn't know what these mean
	target_compile_options(Tests PUBLIC -Og -ggdb
		-fpermissive)
endif()
