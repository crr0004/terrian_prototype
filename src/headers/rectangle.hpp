#ifndef RECTANGLE_H
#define RECTANGLE_H 1
#include "polygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace Geometry {
	class Rectangle : public Polygon{
		public:
			Rectangle();
			void buildStatic() ;
			void draw() ;
			void setLengths(float, float);
			~Rectangle();
		private:
			GLuint vboID[1];

	};
} // namespace Geometry
#endif /* ifndef RECTANGLE_H */
