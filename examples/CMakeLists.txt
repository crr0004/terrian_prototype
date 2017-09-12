cmake_minimum_required(VERSION 3.6)

SET(1_EXAMPLE_NAME one)
SET(2_EXAMPLE_NAME bullet)
SET(3_EXAMPLE_NAME basic)
SET(4_EXAMPLE_NAME rectangle)
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

add_executable(${1_EXAMPLE_NAME} ${1_SRC})
target_link_libraries(${1_EXAMPLE_NAME} ${LIBS})
add_executable(${2_EXAMPLE_NAME} ${2_SRC})
target_link_libraries(${2_EXAMPLE_NAME} ${LIBS})
add_executable(${3_EXAMPLE_NAME} ${3_SRC})
target_link_libraries(${3_EXAMPLE_NAME} ${LIBS})
add_executable(${4_EXAMPLE_NAME} ${4_SRC})
target_link_libraries(${4_EXAMPLE_NAME} ${LIBS})

set_property(TARGET ${1_EXAMPLE_NAME} PROPERTY CXX_STANDARD 98)
set_property(TARGET ${2_EXAMPLE_NAME} PROPERTY CXX_STANDARD 98)
#Compiler options for Visual Studios
if(MSVC)
	target_compile_options(${1_EXAMPLE_NAME} PRIVATE "/W4")

else()
	#Visual studio is a bit dumb and doesn't know what these mean
	target_compile_options(${1_EXAMPLE_NAME} PUBLIC -O1 -g)
	target_compile_options(${2_EXAMPLE_NAME} PUBLIC -ggdb)
	
endif()
