#ifndef POLYGON_H
#define POLYGON_H
#include "IPolygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Terrian_Prototype{
	namespace Geometry {
		class Polygon : public IPolygon {
		public:
			Polygon();
			virtual	void setVertices(GLfloat vertices[], unsigned int size);
			virtual	void setIndices(GLuint indices[], unsigned int size);
			virtual	GLfloat* getVertices();
			virtual	GLuint* getIndices();
			virtual	void buildStatic();
			virtual	void setShaderLocations(GLuint vertShaderLocation);
			virtual	void draw(struct LogicContext* state);

			virtual	void update(struct LogicContext* state);
			virtual	void translate(glm::vec3 moveBy);
			virtual	void rotate(glm::vec3 rotateAround, float rotateBy);
			virtual	glm::mat4* getModelMatrix();
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
	}
}

#endif
