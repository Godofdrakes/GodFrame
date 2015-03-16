#ifndef _OPENGL_TOOLS_H_
#define _OPENGL_TOOLS_H_

#define CheckGLError( description ) \
{\
	GLenum glError = glGetError( );\
	switch( glError ) {\
	case GL_NO_ERROR:\
		break;\
	case GL_INVALID_ENUM:\
		assert( 0 && description && "GL_INVALID_ENUM" );\
		break;\
	case GL_INVALID_VALUE:\
		assert( 0 && description && "GL_INVALID_VALUE" );\
		break;\
	case GL_INVALID_OPERATION:\
		assert( 0 && description && "GL_INVALID_OPERATION" );\
		break;\
	case GL_INVALID_FRAMEBUFFER_OPERATION:\
		assert( 0 && description && "GL_INVALID_FRAMEBUFFER_OPERATION" );\
		break;\
	case GL_OUT_OF_MEMORY:\
		assert( 0 && description && "GL_OUT_OF_MEMORY" );\
		break;\
	default:\
		assert( 0 && description && "default" );\
		break;\
	}\
}\

#include <GL\glew.h>

#include <GLFW\glfw3.h>

#endif
