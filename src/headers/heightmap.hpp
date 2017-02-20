#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include <glm/glm.hpp>
#include "logiccontext.hpp"
#include "polygon.hpp"
	struct HeightmapSettings{
		int	width; //how large is the map
		int depth;
		int	widthDensity; //how many triangles are there
		//int	depthDensity; //not using this at the moment. Assuming a square
		glm::vec3 origin;
		HeightmapSettings(){
			width = -1;
			depth = -1;
			widthDensity = -1;
		}
	};

	class Heightmap{
		public:
			Heightmap();
			~Heightmap();
			Heightmap(GLfloat* vertices, GLuint* indices);
			Heightmap(HeightmapSettings settings);
			Heightmap(HeightmapSettings* settings);
			void build(HeightmapSettings settings);
			void build(HeightmapSettings *settings);
			void draw(LogicContext* state);
			void update(LogicContext* state);
			void setShaderLocations(GLuint vertShaderLocation);
			int getIndexOfSquareIntersectingLine(glm::vec3 a, glm::vec3 b);
			int getIndexOfSquare(int squareNumber);
			int getIndexOfSquareVertex(int squareNumber, int vertexNumber);
			void rotate(glm::vec3 rotateAround, float rotateBy);
			int getSquareCount();
			HeightmapSettings* getSettings();
		protected:
			void addVertex(float vertex);
			void addVertex(float v1, float v2, float v3);
			void addIndex(unsigned int index);

		private:
			Geometry::Polygon polygon;
			int verticesPosition;
			int indicesPosition;
			int squareCount;
			HeightmapSettings* settings;
			GLfloat* vertices;
			GLuint* indices;

	};
#endif /* ifndef HEIGHTMAP_H */
