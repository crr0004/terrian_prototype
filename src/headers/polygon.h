#ifndef POLYGON_H
#define POLYGON_H
#include <GL/glew.h>

class Polygon{
	public:
		Polygon();
		void setVertices(GLfloat vertices[], unsigned int size);
		void setIndices(GLuint indices[], unsigned int size);
		void buildStatic();
		void setShaderLocations(GLuint vertShaderLocation);
		void draw();
		~Polygon();

	private:
		unsigned int vertexSize;
		unsigned int indicesSize;
		GLfloat *vertices;
		GLuint *indices;
		GLuint vboID[2];
		GLuint vertShaderLocation;
};

#endif
