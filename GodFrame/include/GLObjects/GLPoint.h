#ifndef _GLPOINT_H_
#define _GLPOINT_H_

#include "GLPrimitive.h"

class GLPoint : public GLPrimitive {

private:

public:

	GLPoint( GLuint shader, glm::mat4 projection );
	~GLPoint( void );

	DERIVED_GL_PRIMITIVE

};

#endif
