#ifndef TRIANGLE_H
#define TRIANGLE_H 1
#include "polygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace Geometry {
	class Triangle : public Polygon{
		public:
			Triangle();
			void buildStatic() ;
			void draw() ;
			void setStartEnd(const glm::vec3 a, const glm::vec3 b);
			~Triangle();
		private:
			GLuint vboID[1];

	};
} // namespace Geometry
#endif /* ifndef TRIANGLE_H */
