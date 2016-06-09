#ifndef LOGICSTATE_H
#define LOGICSTATE_H 1
#include <glm/glm.hpp>
#include <GL/glew.h>

struct LogicState {
	//This should go into a shader state.
	GLuint uloc_modelview;
	glm::mat4 modelview;
};
#endif /* ifndef LOGICSTATE_H */
