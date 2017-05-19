#ifndef LINE_H
#define LINE_H 1
#include "polygon.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace Geometry{
class Line : public Polygon{
	public:
		Line();
		void buildStatic() ;
		void draw() ;
		void setStartEnd(const glm::vec3 a, const glm::vec3 b);
		~Line();
	private:
		GLuint vboID[1];

};
} //namespace Geometry
#endif /* ifndef LINE_H */
