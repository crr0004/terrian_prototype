#ifndef ARRAYBUFFERBUILDER_H
#define ARRAYBUFFERBUILDER_H
#include "IArrayBufferBuilder.hpp"
class ArrayBufferBuilt : public IArrayBufferBuilt {
	friend class ArrayBufferBuilder;
	public:
		void draw();
		void buffer();
		void enable();
		void disable();
		void setBufferID(GLuint);
		~ArrayBufferBuilt();
	protected:
		ArrayBufferBuilt();
	private:
		GLsizei arrayCount;
		GLvoid* source;
		GLenum drawMode;
		GLenum target;
		GLenum mode;
		GLint first;
		GLsizeiptr bufferSize;
		GLenum drawUsage;
		GLuint id;
		bool buffered;
};
class ArrayBufferBuilder : public IArrayBufferBuilder {
	public:
		IArrayBufferBuilder* clone();
		void setArrayCount(GLsizei);
		void setSource(GLvoid*);
		void setMode(GLenum);
		void setFirst(GLint);
		void setTarget(GLenum);
		void setBufferSize(GLsizeiptr);
		void setDrawUsage(GLenum);
		~ArrayBufferBuilder();
		ArrayBufferBuilder();
	private:
		ArrayBufferBuilt* arrayBuffer;
};
#endif
