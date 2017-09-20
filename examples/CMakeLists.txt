cmake_minimum_required(VERSION 3.6)
set(EXAMPLES 
	one 
	bullet 
	basic 
	rectangle 
	bullet_collision
	bullet_integration
	physics
	)

foreach(EXAMPLE_NAME ${EXAMPLES})
	
	IF(EXISTS ${PROJECT_SOURCE_DIR}/examples/${EXAMPLE_NAME}.cpp)
		add_executable(${EXAMPLE_NAME}_EXAMPLE ${PROJECT_SOURCE_DIR}/examples/${EXAMPLE_NAME}.cpp)
		target_link_libraries(${EXAMPLE_NAME}_EXAMPLE ${LIBS})
		target_compile_options(${EXAMPLE_NAME}_EXAMPLE PUBLIC -ggdb)
	ELSEIF(EXISTS "${PROJECT_SOURCE_DIR}/examples/${EXAMPLE_NAME}/CMakeLists.txt")
			add_subdirectory(${EXAMPLE_NAME})
	ENDIF()
endforeach(EXAMPLE_NAME)

#Old way of creating examples

#[[
SET(1_EXAMPLE_NAME one)
SET(2_EXAMPLE_NAME bullet)
SET(3_EXAMPLE_NAME basic)
SET(4_EXAMPLE_NAME rectangle)
SET(5_EXAMPLE_NAME bullet_collision)
SET(1_SRC
	${PROJECT_SOURCE_DIR}/examples/${1_EXAMPLE_NAME}.cpp
	)
SET(2_SRC
	${PROJECT_SOURCE_DIR}/examples/${2_EXAMPLE_NAME}.cpp
	)
SET(3_SRC
	${PROJECT_SOURCE_DIR}/examples/${3_EXAMPLE_NAME}.cpp
	)
SET(4_SRC
	${PROJECT_SOURCE_DIR}/examples/${4_EXAMPLE_NAME}.cpp
	)
SET(5_SRC
	${PROJECT_SOURCE_DIR}/examples/${5_EXAMPLE_NAME}.cpp
	)

add_executable(${1_EXAMPLE_NAME}
	${1_SRC})
target_link_libraries(${1_EXAMPLE_NAME}
	${LIBS})
add_executable(${2_EXAMPLE_NAME}
	${2_SRC})
target_link_libraries(${2_EXAMPLE_NAME}
	${LIBS})
add_executable(${3_EXAMPLE_NAME}
	${3_SRC})
target_link_libraries(${3_EXAMPLE_NAME}
	${LIBS})
add_executable(${4_EXAMPLE_NAME}
	${4_SRC})
target_link_libraries(${4_EXAMPLE_NAME}
	${LIBS})
add_executable(${5_EXAMPLE_NAME}
	${5_SRC})
target_link_libraries(${5_EXAMPLE_NAME}
	${LIBS})

set_property(TARGET
	${1_EXAMPLE_NAME} PROPERTY
	CXX_STANDARD 98)
set_property(TARGET
	${2_EXAMPLE_NAME} PROPERTY
	CXX_STANDARD 98)
#Compiler options for Visual Studios
if(MSVC)
	target_compile_options(${1_EXAMPLE_NAME}
		PRIVATE "/W4")

else()
	#Visual studio is a bit dumb and doesn't know what these mean
	target_compile_options(${1_EXAMPLE_NAME}
		PUBLIC -O1 -g)
	target_compile_options(${2_EXAMPLE_NAME}
		PUBLIC
		-ggdb)

endif()
]]
