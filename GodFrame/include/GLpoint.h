#ifndef _GLPOINT_H_
#define _GLPOINT_H_

#include <assert.h>
#include "OpenGL_Tools.h"
#include "GLprimitive.h"

/* THOUGHTS FORM LAST TIME:
	What steps must be taken to make a point?
	What should a point ( or any GLprimitive ) be able to do?
	How can we better hide the OpenGL side of things from the user?
	Finish Draw function.
*/

class GLpoint : public GLprimitive {

private:
	Vertex vert;
	glm::vec2 data_vertex;

public:

	DERIVED_GL_PRIMITIVE

};

#endif
