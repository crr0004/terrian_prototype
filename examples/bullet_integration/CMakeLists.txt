cmake_minimum_required(VERSION 3.6)

set(EXAMPLE_NAME bullet_integration)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(${EXAMPLE_NAME}_EXAMPLE 
	${PROJECT_SOURCE_DIR}/examples/bullet_integration/${EXAMPLE_NAME}.cpp
	${PROJECT_SOURCE_DIR}/examples/bullet_integration/print_node.cpp
	#Easy to copy and paste this
	#${PROJECT_SOURCE_DIR}/examples/bullet_integration/.cpp
	)
target_link_libraries(${EXAMPLE_NAME}_EXAMPLE ${LIBS})
target_compile_options(${EXAMPLE_NAME}_EXAMPLE PUBLIC -ggdb)
