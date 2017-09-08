cmake_minimum_required(VERSION 3.6)

SET(ONE_EXAMPLE_NAME one)
SET(TWO_EXAMPLE_NAME bullet)
SET(ONE_SRC
	${PROJECT_SOURCE_DIR}/examples/${ONE_EXAMPLE_NAME}.cpp
	)
SET(TWO_SRC
	${PROJECT_SOURCE_DIR}/examples/${TWO_EXAMPLE_NAME}.cpp
	)

add_executable(${ONE_EXAMPLE_NAME} ${ONE_SRC})
target_link_libraries(${ONE_EXAMPLE_NAME} ${LIBS})
add_executable(${TWO_EXAMPLE_NAME} ${ONE_SRC})
target_link_libraries(${TWO_EXAMPLE_NAME} ${LIBS})

set_property(TARGET ${ONE_EXAMPLE_NAME} PROPERTY CXX_STANDARD 98)
set_property(TARGET ${TWO_EXAMPLE_NAME} PROPERTY CXX_STANDARD 98)
#Compiler options for Visual Studios
if(MSVC)
	target_compile_options(${ONE_EXAMPLE_NAME} PRIVATE "/W4")

else()
	#Visual studio is a bit dumb and doesn't know what these mean
	target_compile_options(${ONE_EXAMPLE_NAME} PUBLIC -O1 -g)
	
endif()
