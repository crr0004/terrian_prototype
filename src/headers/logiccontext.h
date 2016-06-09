#ifndef LOGICCONTEXT_H
#define LOGICCONTEXT_H 1
#include <glm/glm.hpp>
#include <GL/glew.h>

struct LogicContext {
	//This should go into a shader state.
	GLuint uloc_modelview;
	glm::mat4 modelview;
};
#endif /* ifndef LOGICCONTEXT_H */
