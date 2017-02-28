#ifndef IDRAWBUILDER_H
#define IDRAWBUILDER_H
class IDrawBuilder {
	public:
		virtual ~IDrawBuilder(){}
		virtual IDrawBuilder* clone() = 0;
};
#endif
