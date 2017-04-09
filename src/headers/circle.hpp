#ifndef CIRCLE_H
#define CIRCLE_H 1
#include "IPolygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
class Circle : public IPolygon{
	public:
		Circle();
		void setVertices(GLfloat vertices[], unsigned int size) ;
		void setIndices(GLuint indices[], unsigned int size){}
		GLuint* getIndices(){return 0;}
		GLfloat* getVertices() ;
		unsigned int getVertexSize();
		void buildStatic() ;
		void setShaderLocations(GLuint vertShaderLocation) ;
		void setShaderLocations(const char* name);
		void draw(struct LogicContext* state) ;

		void update(struct LogicContext* state) ;
		void translate(glm::vec3 moveBy) ;
		void rotate(glm::vec3 rotateAround, float rotateBy) ;
		glm::mat4* getModelMatrix() ;
		void setStartEnd(const glm::vec3 a, const glm::vec3 b);
		~Circle();
	private:
		unsigned int vertexSize;
		GLfloat *vertices;
		GLuint vboID[1];
		GLuint vertShaderLocation;
		glm::mat4 model_matrix;

};
#endif /* ifndef CIRCLE_H */
