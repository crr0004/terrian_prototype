#ifndef POLYGON_H
#define POLYGON_H
#include "node.hpp"
#include "logiccontext.hpp"
#include "geometry/moveable.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace Geometry {
	class Polygon : public Node {
		public:
			Polygon();
			virtual	void setVertices(GLfloat vertices[], unsigned int size);
			virtual	void setIndices(GLuint indices[], unsigned int size);
			virtual	GLfloat* getVertices();
			virtual	GLuint* getIndices();
			virtual unsigned int getVertexSize();
			virtual	void buildStatic();
			virtual	void setShaderLocations(GLuint vertShaderLocation);
			void setShaderLocations(const char* name);
			virtual void setLogicContext(LogicContext* state);
			virtual	void draw();
			virtual	void update();
			virtual	void translate(glm::vec3 moveBy);
			virtual	void rotate(glm::vec3 rotateAround, float rotateBy);
			virtual	glm::mat4* getModelMatrix();
			virtual Moveable& getMoveable();
			~Polygon();
			//Node methods
			virtual void operation();

		protected:
			LogicContext* state;
			unsigned int vertexSize;
			unsigned int indicesSize;
			GLfloat *vertices;
			GLuint *indices;
			GLuint vertShaderLocation;
			Moveable moveable;	
		private:
			GLuint vboID[2];
	};
} //namespace Geometry
#endif
