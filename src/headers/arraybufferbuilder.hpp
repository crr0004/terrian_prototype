#ifndef ARRAYBUFFERBUILDER_H
#define ARRAYBUFFERBUILDER_H
#include "IArrayBufferBuilder.hpp"
class ArrayBufferBuilt : public IArrayBufferBuilt {
	friend class ArrayBufferBuilder;
	public:
		void draw();
		void enable();
		void disable();
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
		void setSource(const GLvoid*);
		void setMode(GLenum);
		void setFirst(GLint);
		void setTarget(GLenum);
		void setBufferSize(GLsizeiptr);
		void setDrawUsage(GLenum);
		~ArrayBufferBuilder();
	protected:
		ArrayBufferBuilder();
	private:
		ArrayBufferBuilt* arraybuilt;
};
#endif
