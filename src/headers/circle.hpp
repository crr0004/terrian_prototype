#ifndef CIRCLE_H
#define CIRCLE_H 1
#include "polygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace Geometry {
class Circle : public Polygon{
	public:
		Circle();
		void buildStatic() ;
		void draw() ;
		void setStartEnd(const glm::vec3 a, const glm::vec3 b);
		~Circle();
	private:
		GLuint vboID[1];
};
} // namespace Geometry
#endif /* ifndef CIRCLE_H */
