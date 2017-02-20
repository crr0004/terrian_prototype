#ifndef TRIANGLE_H
#define TRIANGLE_H 1
#include "IPolygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
class Triangle : public IPolygon{
	public:
		Triangle();
		void setVertices(GLfloat vertices[], unsigned int size) ;
		void setIndices(GLuint indices[], unsigned int size){}
		GLuint* getIndices(){return 0;}
		GLfloat* getVertices() ;
		void buildStatic() ;
		void setShaderLocations(GLuint vertShaderLocation) ;
		void draw(struct LogicContext* state) ;

		void update(struct LogicContext* state) ;
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
#endif /* ifndef TRIANGLE_H */
