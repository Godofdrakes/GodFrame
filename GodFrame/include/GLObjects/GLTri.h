#ifndef _GLTRI_H_
#define _GLTRI_H_

#include "GLPrimitive.h"

class GLTri : public GLPrimitive {

private:

public:

	GLTri( GLuint shader, glm::mat4 projection );
	~GLTri( void );

	DERIVED_GL_PRIMITIVE

};

#endif
