#ifndef POLYGON_H
#define POLYGON_H
#include <GL/glew.h>
#include <glm/glm.hpp>

class Polygon{
	public:
		Polygon();
		void setVertices(GLfloat vertices[], unsigned int size);
		void setIndices(GLuint indices[], unsigned int size);
		GLfloat* getVertices();
		GLuint* getIndices();
		void buildStatic();
		void setShaderLocations(GLuint vertShaderLocation);
		void draw(struct LogicContext* state);

		void update(struct LogicContext* state);
		void translate(glm::vec3 moveBy);
		glm::mat4* getModelMatrix();
		~Polygon();

	private:
		unsigned int vertexSize;
		unsigned int indicesSize;
		GLfloat *vertices;
		GLuint *indices;
		GLuint vboID[2];
		GLuint vertShaderLocation;
		glm::mat4 model_matrix;
};

#endif
