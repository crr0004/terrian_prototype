#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "node.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace Geometry {
	class Moveable : public Node{
		public:
			Moveable();
			virtual void operation();
			virtual void add(INode*);
			virtual int visit(Moveable*);
			virtual int visit(INode* node);
			virtual	void translate(glm::vec3 moveBy);
			virtual void translate(glm::mat4&);
			virtual void parentTranslate(glm::mat4);
			virtual	void rotate(glm::vec3 rotateAround, float rotateBy);
			virtual void push();
			virtual void pop();
			virtual	glm::mat4* getModelMatrix();
			virtual glm::mat4 getCulumativeMatrix();
			virtual glm::mat4* getTransitiveMatrix();
			virtual ~Moveable();
		protected:
			glm::mat4 model_matrix;
			glm::mat4 transitiveMatrix;
	};
} // namespace Geometry
#endif
