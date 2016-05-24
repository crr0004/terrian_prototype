/**To Replace this:
//Triangle test vertices
	GLuint vboID[2];
	GLfloat vertices[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.1f, 1.0f,
		0.1f, 0.0f, 1.0f,
		0.1f, 0.1f, 1.0f
			};


	GLuint indices[] = {
		//Front face
		0, 2, 1,
		1, 3, 2,

	};

	
	int vertexCount = sizeof(indices) / sizeof(GLuint);

	glGenBuffers(2, &vboID[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


*/
#ifdef POLYGON_H
#define POLYGON_H
#include <GL/glew.h>

class Polygon{
	public:
		Polygon(

	private:
		unsigned int vertexSize;
		unsigned int indexSize;


}



#endif
