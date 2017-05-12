#ifndef TRIANGLE_H
#define TRIANGLE_H 1
#include "polygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace Geometry {
	class Triangle : public Polygon{
		public:
			Triangle();
			void setVertices(GLfloat vertices[], unsigned int size) ;
			void setIndices(GLuint indices[], unsigned int size){}
			GLuint* getIndices(){return 0;}
			GLfloat* getVertices() ;
			unsigned int getVertexSize();
			void buildStatic() ;
			void setShaderLocations(GLuint vertShaderLocation) ;
			void setShaderLocations(const char* name);
			void draw() ;
			void update() ;
			void translate(glm::vec3 moveBy) ;
			void rotate(glm::vec3 rotateAround, float rotateBy) ;
			glm::mat4* getModelMatrix() ;
			void setStartEnd(const glm::vec3 a, const glm::vec3 b);
			~Triangle();
		private:
			unsigned int vertexSize;
			GLfloat *vertices;
			GLuint vboID[1];
			GLuint vertShaderLocation;
			glm::mat4 model_matrix;

	};
} // namespace Geometry
#endif /* ifndef TRIANGLE_H */
