#ifndef MATRIXSTACKSINGLETON_H
#define MATRIXSTACKSINGLETON_H
#include <glm/glm.hpp>
class MatrixStackSingleton{
	public:
		static MatrixStackSingleton* instance();
		static void Destroy();
		glm::mat4 push(glm::mat4 m);
		glm::mat4 pop();
	protected:
		MatrixStackSingleton();
		~MatrixStackSingleton();
	private:
		static MatrixStackSingleton* _instance;
};
#endif
