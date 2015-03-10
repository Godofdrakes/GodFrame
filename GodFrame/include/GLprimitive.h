#ifndef _GLPRIMITIVE_H_
#define _GLPRIMITIVE_H_

#include "OpenGL_Tools.h"

struct Vertex {
	glm::vec2 position, texture;
};

// Interface macro for quick declaration of a large block of code.
// Changes here will be automatically updated for any objects using this macro
// REMEMBER TO UPDATE THE OBJECT'S .CPP FILE AS WELL

// Use BASE_GL_PRIMITIVE for the base class and DERIVED_GL_PRIMITIVE for derived classes. DO NOT USE THE INTERFACE DIRECTLY
#define INTERFACE_GL_PRIMITIVE(terminal) \
protected:\
	virtual void GenBuffers( void ) ##terminal\
	virtual void DestroyBuffers( void ) ##terminal\
	\
	virtual void BindBuffers( void ) ##terminal\
	virtual void BufferVBO( void ) ##terminal\
	virtual void BufferUVO( void ) ##terminal\
	virtual void BufferEBO( void ) ##terminal\
	\
	virtual void SetMVP( glm::mat4 projection ) ##terminal\
	\
public:\
	virtual void LoadTexture( const char* fileName ) ##terminal\
	\
	virtual void SetSize( float set_width, float set_height ) ##terminal \
	virtual void SetSize( glm::vec2 set_size ) ##terminal \
	\
	virtual void SetPosition( float set_x, float set_y ) ##terminal \
	virtual void SetPosition( glm::vec2 set_position ) ##terminal \
	\
	virtual void SetColor( float set_red, float set_green, float set_blue, float set_alpha ) ##terminal \
	virtual void SetColor( glm::vec4 set_color ) ##terminal \
	\
	virtual void SetRotaionRad( float radians ) ##terminal\
	virtual void SetRotaionDeg( float degrees ) ##terminal\
	\
	virtual void Draw( void ) ##terminal\

#define BASE_GL_PRIMITIVE		INTERFACE_GL_PRIMITIVE(=0;)
#define DERIVED_GL_PRIMITIVE	INTERFACE_GL_PRIMITIVE(;)

class GLprimitive {

protected:
	glm::vec3 scale, position;
	glm::vec4 color;
	glm::mat4 model, rotation, view, mvp;
	GLuint texture, ebo, uvo, vbo, vao, shaderProgram, vertexShader, fragmentShader;
	GLint posAttrib, texAttrib;

public:
	virtual ~GLprimitive( ) {};

	BASE_GL_PRIMITIVE

};
		

#endif
