#ifndef IVERTEXATTRIBUTEBUILDER_H
#define IVERTEXATTRIBUTEBUILDER_H
#include <glad/glad.h>
class IVertexAttributeBuilt {
	public:
		virtual ~IVertexAttributeBuilt(){}
		virtual void enable() = 0;
		virtual void bind() = 0;
		virtual void disable() = 0;
};
class IVertexAttributeBuilder {
	public:
		virtual ~IVertexAttributeBuilder(){}
		virtual IVertexAttributeBuilder* clone() = 0;
		virtual void setLocation(GLuint) = 0;
		virtual void setType(GLenum) = 0;
		virtual void setSetNormalized(GLboolean) = 0;
		virtual void setAttributeSize(GLint) = 0;
		virtual void setStride(GLsizei) = 0;
		virtual void setOffset(const GLvoid*) = 0;
		virtual IVertexAttributeBuilt* build() = 0;
};
#endif
