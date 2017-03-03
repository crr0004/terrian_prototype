#ifndef VERTEXATTRIBUTEBUILDER_H
#define VERTEXATTRIBUTEBUILDER_H
#include "IVertexAttributeBuilder.hpp"
#include <glad/glad.h>
class VertexAttributeBuilt : public IVertexAttributeBuilt {
	friend class VertexAttributeBuilder;
	public:
		~VertexAttributeBuilt(){}
		void enable();
		void bind();
		void disable();
	protected:
		VertexAttributeBuilt();
	private:
		GLuint location;
		GLenum type;
		GLboolean normalized;
		GLint size;
		GLsizei stride;
		const GLvoid* offset;
};
class VertexAttributeBuilder : public IVertexAttributeBuilder{
	public:
		IVertexAttributeBuilder* clone();
		VertexAttributeBuilder();
		~VertexAttributeBuilder();
		void setLocation(GLuint);
		void setType(GLenum);
		void setSetNormalized(GLboolean);
		void setAttributeSize(GLint);
		void setStride(GLsizei);
		void setOffset(const GLvoid*);
		IVertexAttributeBuilt* build();
	private:
		VertexAttributeBuilt* vertex;
};
#endif
