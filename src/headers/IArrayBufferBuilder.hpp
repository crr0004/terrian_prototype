#ifndef IARRAYBUFFERBUILDER_H
#define IARRAYBUFFERBUILDER_H
#include <glad/glad.h>
class IArrayBufferBuilt {
	public:
		virtual void draw() = 0;
		virtual void enable() = 0;
		virtual void disable() = 0;
		virtual void buffer() = 0;
};
class IArrayBufferBuilder{
	public:
		virtual ~IArrayBufferBuilder(){}
		IArrayBufferBuilder();
		virtual IArrayBufferBuilder* clone() = 0;
		/*

	arrayDraw->numberOfArrays(1);
	arrayDraw->setSize(vertexSize);
	arrayDraw->setVertices(vertices);
	arrayDraw->setType(GL_TRIANGLES);
	arrayDraw->setStartingIndex(0);
	*/
		virtual void setArrayCount(GLsizei) = 0;
		virtual void setVerticesPoint(const GLvoid*) = 0;
		virtual void setMode(GLenum) = 0;
		virtual void setFirst(GLint) = 0;
		virtual void setTarget(GLenum) = 0;
		virtual void setBufferSize(GLsizeiptr) = 0;
		virtual void setDrawUsage(GLenum) = 0;
};
#endif
