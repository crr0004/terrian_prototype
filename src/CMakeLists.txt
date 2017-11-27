cmake_minimum_required(VERSION 3.6)

SET(MAIN_SRC
	${PROJECT_SOURCE_DIR}/src/src/line.cpp
	${PROJECT_SOURCE_DIR}/src/src/matrixstacksingleton.cpp 
	${PROJECT_SOURCE_DIR}/src/src/polygon.cpp 
	${PROJECT_SOURCE_DIR}/src/src/visualcontext.cpp 
	${PROJECT_SOURCE_DIR}/src/src/luae/scriptheightmap.cpp
	${PROJECT_SOURCE_DIR}/src/src/heightmap.cpp 
	${PROJECT_SOURCE_DIR}/src/src/glad.c
	${PROJECT_SOURCE_DIR}/src/src/luae/script.cpp
	${PROJECT_SOURCE_DIR}/src/src/luae/scriptmanager.cpp
	${PROJECT_SOURCE_DIR}/src/src/luae/table.cpp
	${PROJECT_SOURCE_DIR}/src/src/triangle.cpp
	${PROJECT_SOURCE_DIR}/src/src/circle.cpp
	${PROJECT_SOURCE_DIR}/src/src/rectangle.cpp
	${PROJECT_SOURCE_DIR}/src/src/luae/scriptriangle.cpp
	${PROJECT_SOURCE_DIR}/src/src/addtodrawqueue.cpp
	${PROJECT_SOURCE_DIR}/src/src/luae/scriptmouse.cpp
	${PROJECT_SOURCE_DIR}/src/src/luae/scriptcollision.cpp
	${PROJECT_SOURCE_DIR}/src/src/node.cpp
	${PROJECT_SOURCE_DIR}/src/src/collision_simpleworld.cpp
	${PROJECT_SOURCE_DIR}/src/src/collision_aabbcollider.cpp
	${PROJECT_SOURCE_DIR}/src/src/collision_sphere.cpp
	${PROJECT_SOURCE_DIR}/src/src/geometry_moveable.cpp
	${PROJECT_SOURCE_DIR}/src/src/bullet_node.cpp
	${PROJECT_SOURCE_DIR}/src/src/bullet_contactmanifold_node.cpp
	${PROJECT_SOURCE_DIR}/src/src/dynamic_node.cpp
	${PROJECT_SOURCE_DIR}/src/src/dynamic_driver.cpp
	)
SET(JELLY_ENGINE_SRC ${MAIN_SRC} PARENT_SCOPE)

SET(MAIN_HEADERS
	${PROJECT_SOURCE_DIR}/src/headers/collision/AABB.hpp
	${PROJECT_SOURCE_DIR}/src/headers/collision/aabbcollider.hpp
	${PROJECT_SOURCE_DIR}/src/headers/collision/collider.hpp
	${PROJECT_SOURCE_DIR}/src/headers/collision/notification_command.hpp
	${PROJECT_SOURCE_DIR}/src/headers/collision/plane.hpp
	${PROJECT_SOURCE_DIR}/src/headers/collision/simpleworld.hpp
	${PROJECT_SOURCE_DIR}/src/headers/collision/spherecollider.hpp
	${PROJECT_SOURCE_DIR}/src/headers/geometry/moveable.hpp
	${PROJECT_SOURCE_DIR}/src/headers/geometry/point.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/luae.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/script.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/scriptcollision.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/scriptheightmap.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/scriptmanager.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/scriptmouse.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/scriptriangle.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/table.hpp
	${PROJECT_SOURCE_DIR}/src/headers/luae/Utilities.hpp
	${PROJECT_SOURCE_DIR}/src/headers/patterns/builder.hpp
	${PROJECT_SOURCE_DIR}/src/headers/patterns/command.hpp
	${PROJECT_SOURCE_DIR}/src/headers/addtodrawqueue.hpp
	${PROJECT_SOURCE_DIR}/src/headers/circle.hpp
	${PROJECT_SOURCE_DIR}/src/headers/rectangle.hpp
	${PROJECT_SOURCE_DIR}/src/headers/gldebug.hpp
	${PROJECT_SOURCE_DIR}/src/headers/heightmap.hpp
	${PROJECT_SOURCE_DIR}/src/headers/INode.hpp
	${PROJECT_SOURCE_DIR}/src/headers/line.hpp
	${PROJECT_SOURCE_DIR}/src/headers/logiccontext.hpp
	${PROJECT_SOURCE_DIR}/src/headers/matrixstacksingleton.hpp
	${PROJECT_SOURCE_DIR}/src/headers/node.hpp
	${PROJECT_SOURCE_DIR}/src/headers/polygon.hpp
	${PROJECT_SOURCE_DIR}/src/headers/terrian_config.hpp
	${PROJECT_SOURCE_DIR}/src/headers/triangle.hpp
	${PROJECT_SOURCE_DIR}/src/headers/visualcontext.hpp
	${PROJECT_SOURCE_DIR}/src/headers/VisualServer.hpp
	${PROJECT_SOURCE_DIR}/src/headers/bullet_node.hpp
	${PROJECT_SOURCE_DIR}/src/headers/bullet_contactmanifold_node.hpp
	${PROJECT_SOURCE_DIR}/src/headers/dynamics/dynamic_node.hpp
	${PROJECT_SOURCE_DIR}/src/headers/dynamics/dynamic_driver.hpp

	)

set(JELLY_ENGINE_HEADERS ${MAIN_HEADERS} PARENT_SCOPE)

#message(STATUS ${MAIN_SRC})

add_library(jellyEngine ${MAIN_SRC} ${MAIN_HEADERS})
target_link_libraries(jellyEngine ${LIBS})
SET(LIBS ${LIBS} jellyEngine)
SET(LIBS ${LIBS} PARENT_SCOPE)

if(${CMAKE_VERSION} VERSION_GREATER "3.8.2")
	source_group(TREE "${PROJECT_SOURCE_DIR}/src/" FILES ${MAIN_HEADERS})
	source_group(TREE "${PROJECT_SOURCE_DIR}/src/src/" PREFIX "Source Files\\src" FILES ${MAIN_SRC})

endif()

#Compiler options for Visual Studios
if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -W0")
	set_source_files_properties(
	  src/glad.c
	  PROPERTIES
	  COMPILE_FLAGS "-W0"
	)


else()
	
endif()
