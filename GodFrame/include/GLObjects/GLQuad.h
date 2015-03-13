#ifndef _GLQUAD_H_
#define _GLQUAD_H_

#include "GLPrimitive.h"

class GLQuad : public GLPrimitive {

private:

public:

	GLQuad( GLuint shader, glm::mat4 projection );
	~GLQuad( void );

	DERIVED_GL_PRIMITIVE

};

#endif
