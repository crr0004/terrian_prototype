#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include <glm/glm.hpp>
#include "logiccontext.h"
#include "polygon.h"
namespace HeightmapName{
	struct HeightmapSettings{
		int	width; //how large is the map
		int depth;
		int	widthDensity; //how many triangles are there
		//int	depthDensity; //not using this at the moment. Assuming a square
		glm::vec3 origin;
	};

	class Heightmap{
		public:
			Heightmap();
			void build(HeightmapSettings settings);
			void draw(LogicContext* state);
			void update(LogicContext* state);
			void setShaderLocations(GLuint vertShaderLocation);
		protected:
			void foo(){};
		private:
			Polygon polygon;

	};
}
#endif /* ifndef HEIGHTMAP_H */
