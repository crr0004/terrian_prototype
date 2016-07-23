#ifndef IPOLYGON_H
#define IPOLYGON_H 1
#include <GL/glew.h>
#include <glm/glm.hpp>
class IPolygon{
	public:
		virtual void setVertices(GLfloat vertices[], unsigned int size) = 0;
		virtual void setIndices(GLuint indices[], unsigned int size) = 0;
		virtual GLfloat* getVertices() = 0;
		virtual GLuint* getIndices() = 0;
		virtual void buildStatic() = 0;
		virtual void setShaderLocations(GLuint vertShaderLocation) = 0;
		virtual void draw(struct LogicContext* state) = 0;

		virtual void update(struct LogicContext* state) = 0;
		virtual void translate(glm::vec3 moveBy) = 0;
		virtual void rotate(glm::vec3 rotateAround, float rotateBy) = 0;
		virtual glm::mat4* getModelMatrix() = 0;
		virtual ~IPolygon(){}

};
#endif /* ifndef IPOLYGON_H */
