#include <catch.hpp>
#include <fakeit.hpp>
#include "renderfactory.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <iostream>
#include "matrixstacksingleton.hpp"
#include "logiccontext.hpp"
#include "visualcontext.hpp"
#include "terrian_config.hpp"

#include "IDrawBuilder.hpp"
#include "IArrayBufferBuilder.hpp"
#include "IVertexAttributeBuilder.hpp"
#include "vertexattributebuilder.hpp"
//For stringifying preprocessor values
#define xstr(s) str(s)
#define str(s) #s
#define concat(first, second) first second

TEST_CASE("RenderFactory basic usage"){
	SECTION("Setting prototypes"){
		using namespace fakeit;
		RenderFactory* factory = new RenderFactory();
		Mock<IDrawBuilder> drawMock;
		Mock<IArrayBufferBuilder> arrayMock;
		Mock<IVertexAttributeBuilder> vertexMock;

		IDrawBuilder &drawBuilder = drawMock.get();
		IArrayBufferBuilder &arrayBuilder = arrayMock.get();
		IVertexAttributeBuilder &vertBuilder = vertexMock.get();

		factory->setPrototypes(
				&vertBuilder,
				&arrayBuilder,
				&drawBuilder);

		When(Method(drawMock,clone)).Return(&drawBuilder);
		When(Method(arrayMock,clone)).Return(&arrayBuilder);
		When(Method(vertexMock,clone)).Return(&vertBuilder);

		IDrawBuilder *drawBuilderMock = RenderFactory::NewDrawBuilder();
		IVertexAttributeBuilder *vertBuilderMock = 
			RenderFactory::NewVertexAttributeBuilder();
		IArrayBufferBuilder *arrayBuilderMock = 
			RenderFactory::NewArrayBufferBuilder();


		Verify(Method(drawMock,clone));
		Verify(Method(arrayMock,clone));
		Verify(Method(vertexMock,clone));
	}

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}

TEST_CASE("Builders implementation"){
	struct LogicContext logicContext;
	GLFWwindow *window = VisualContext::CreateGLFWWindow(key_callback);
	GLuint shader_program = VisualContext::make_shader_program(concat(xstr(SHADERS_DIR), "/shader.vert"), concat(xstr(SHADERS_DIR), "/shader.frag"));
	glUseProgram(shader_program);
	GLuint uloc_project   = glGetUniformLocation(shader_program, "project");
	GLuint uloc_modelview = glGetUniformLocation(shader_program, "modelview");
	GLuint vertShaderLocation = glGetAttribLocation(shader_program, "vert");

	/* Compute the projection matrix */
	VisualContext::projection_matrix = glm::perspective(VisualContext::view_angle, VisualContext::aspect_ratio, VisualContext::z_near, VisualContext::z_far);
	logicContext.uloc_modelview = uloc_modelview;

	/* Set the camera position  */
	logicContext.modelview = glm::translate(logicContext.modelview, glm::vec3(0.0f, 0.0f, -20.0f));
	logicContext.modelview = glm::rotate(logicContext.modelview, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));

	glViewport(0,0,VisualContext::width, VisualContext::height);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	RenderFactory* renderfactory = new RenderFactory();
	fakeit::Mock<IDrawBuilder> drawMock;
	fakeit::Mock<IArrayBufferBuilder> arrayMock;

	IDrawBuilder &drawBuilder = drawMock.get();
	IArrayBufferBuilder &arrayBuilder = arrayMock.get();
	IVertexAttributeBuilder* vertexBuilder = new VertexAttributeBuilder();

	renderfactory->setPrototypes(
			vertexBuilder,
			&arrayBuilder,
			&drawBuilder);

	SECTION("VertexAttributeBuilder basic usage"){
		IVertexAttributeBuilder* vert = RenderFactory::NewVertexAttributeBuilder();
		vert->setAttributeSize(3);
		vert->setLocation(vertShaderLocation);
		vert->setOffset(0);
		vert->setSetNormalized(GL_FALSE);
		vert->setStride(0);
		vert->setType(GL_FLOAT);
		IVertexAttributeBuilt* vertex = vert->build();

		GLfloat *vertices = new GLfloat[9];
		unsigned int vertexSize = 9;

		vertices[0] = -1.0f;
		vertices[1] = 0.0f;
		vertices[2] = 0.0f;

		vertices[3] = 1.0f;
		vertices[4] = 0.0f;
		vertices[5] = 0.0f;

		vertices[6] = 1.0f;
		vertices[7] = 1.0f;
		vertices[8] = 0.0f;
		GLuint vboID[1];

		glGenBuffers(1, &vboID[0]);

	//	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));
		MatrixStackSingleton* instance = MatrixStackSingleton::instance();
		glm::mat4 model_matrix;

		instance->push(model_matrix);
		model_matrix = logicContext.modelview * model_matrix;

		//VertexAttributeBuilder replaces this to

		//Not this
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

		//Not this
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

		//Not this
		glUniformMatrix4fv(logicContext.uloc_modelview, 1, GL_FALSE, glm::value_ptr(model_matrix));


		//glEnableVertexAttribArray(vertShaderLocation);
		vertex->enable();
		int enabled = 0;
		glGetVertexAttribiv(vertShaderLocation, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
		REQUIRE(enabled > 0);
		enabled = 0;

		vertex->bind();
		float value = -1;
		glGetVertexAttribfv(vertShaderLocation,
				GL_VERTEX_ATTRIB_ARRAY_SIZE,
				&value);
		REQUIRE(value == 3.0);

		value = -1;
		glGetVertexAttribfv(vertShaderLocation,
				GL_VERTEX_ATTRIB_ARRAY_TYPE,
				&value);
		REQUIRE(value == GL_FLOAT);

		value = -1;
		glGetVertexAttribfv(vertShaderLocation,
				GL_VERTEX_ATTRIB_ARRAY_NORMALIZED,
				&value);
		REQUIRE(value == GL_FALSE);

		value = -1;
		glGetVertexAttribfv(vertShaderLocation,
				GL_VERTEX_ATTRIB_ARRAY_STRIDE,
				&value);
		REQUIRE(value == 0);

		/*
		glVertexAttribPointer(
				vertShaderLocation,
				3, //size of attribute
				GL_FLOAT,
				GL_FALSE,
				0, //stride
				(void*)0 //Pointer to the off of the first component of the first element
				);
				*/
		//VertexAttributeBuilder replaces to here
		glDrawArrays(
				GL_TRIANGLES,
				0,
				vertexSize //Amount of indices to draw
				);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		vertex->disable();
		//glDisableVertexAttribArray(vertShaderLocation);

		model_matrix = (MatrixStackSingleton::instance())->pop();
		glfwSwapBuffers(window);
		glfwPollEvents();
	//}

	}
	SECTION("ArrayBuilder basic usage"){
		IVertexAttributeBuilder* array = RenderFactory::NewVertexAttributeBuilder();

		GLfloat *vertices = new GLfloat[9];
		unsigned int vertexSize = 9;

		vertices[0] = -1.0f;
		vertices[1] = 0.0f;
		vertices[2] = 0.0f;

		vertices[3] = 1.0f;
		vertices[4] = 0.0f;
		vertices[5] = 0.0f;

		vertices[6] = 1.0f;
		vertices[7] = 1.0f;
		vertices[8] = 0.0f;
		GLuint vboID[1];

		glGenBuffers(1, &vboID[0]);

	//	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT, GL_FILL);
		glUniformMatrix4fv(uloc_project, 1, GL_FALSE, glm::value_ptr(VisualContext::projection_matrix));
		MatrixStackSingleton* instance = MatrixStackSingleton::instance();
		glm::mat4 model_matrix;

		instance->push(model_matrix);
		model_matrix = logicContext.modelview * model_matrix;

		//VertexAttributeBuilder replaces this to

		//Not this
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

		//Not this
		glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(GLfloat), vertices, GL_DYNAMIC_DRAW);

		//Not this
		glUniformMatrix4fv(logicContext.uloc_modelview, 1, GL_FALSE, glm::value_ptr(model_matrix));


	glEnableVertexAttribArray(vertShaderLocation);

		glVertexAttribPointer(
				vertShaderLocation,
				3, //size of attribute
				GL_FLOAT,
				GL_FALSE,
				0, //stride
				(void*)0 //Pointer to the off of the first component of the first element
				);
		glDrawArrays(
				GL_TRIANGLES,
				0,
				vertexSize //Amount of indices to draw
				);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(vertShaderLocation);

		model_matrix = (MatrixStackSingleton::instance())->pop();
		glfwSwapBuffers(window);
		glfwPollEvents();
	//}

	}

	glDeleteProgram(shader_program);
	glfwDestroyWindow(window);

	glfwTerminate();
}
