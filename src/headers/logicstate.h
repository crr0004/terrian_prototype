#ifndef LOGICCONTEXT_H
#define LOGICCONTEXT_H 1
#include <glm/glm.hpp>
#include <glad/glad.h>

struct LogicContext {
	//This should go into a shader state.
	GLuint uloc_modelview;
	glm::mat4 modelview;
};
#endif /* ifndef LOGICCONTEXT_H */
