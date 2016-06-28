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
			~Heightmap();
			Heightmap(HeightmapSettings settings);
			void build(HeightmapSettings settings);
			void draw(LogicContext* state);
			void update(LogicContext* state);
			void setShaderLocations(GLuint vertShaderLocation);
		protected:
			void addVertex(float vertex);
			void addVertex(float v1, float v2, float v3);
			void addIndex(unsigned int index);
		private:
			Polygon polygon;
			int verticesPosition;
			int indicesPosition;
			int squareCount;
			HeightmapSettings* settings;
			GLfloat* vertices;
			GLuint* indices;

	};
}
#endif /* ifndef HEIGHTMAP_H */
