#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H 1
#include <glm/glm.hpp>
namespace Heightmap{
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
			void build(struct HeightMapSettings settings);
			void draw();

	};
}
#endif /* ifndef HEIGHTMAP_H */
