#ifndef IARRAYBUFFERBUILDER_H
#define IARRAYBUFFERBUILDER_H
class IArrayBufferBuilder{
	public:
		virtual ~IArrayBufferBuilder();
		IArrayBufferBuilder();
		virtual IArrayBufferBuilder* clone() = 0;
};
#endif
