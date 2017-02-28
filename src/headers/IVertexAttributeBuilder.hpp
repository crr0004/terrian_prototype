#ifndef IVERTEXATTRIBUTEBUILDER_H
#define IVERTEXATTRIBUTEBUILDER_H
class IVertexAttributeBuilder {
	public:
		virtual ~IVertexAttributeBuilder(){}
		IVertexAttributeBuilder();
		virtual IVertexAttributeBuilder* clone() = 0;
};
#endif
