#ifndef _GLLINE_H_
#define _GLLINE_H_

#include "GLPrimitive.h"

class GLLine : public GLPrimitive {

private:

public:

	GLLine( GLuint shader, glm::mat4 projection );
	~GLLine( void );

	DERIVED_GL_PRIMITIVE
};

#endif
