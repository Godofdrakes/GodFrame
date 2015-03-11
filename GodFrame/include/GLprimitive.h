#ifndef _GLPRIMITIVE_H_
#define _GLPRIMITIVE_H_

#include "OpenGL_Tools.h"

/* GLPrimitive base/derived planning

GLPrimitive
	Render() = 0;
	Rotate() = 0;
	Scale() = 0;
	Move() = 0;
	Color() = 0;

GLPoint
	Render();
	Rotate(); // Doesn't actually do anything. Why would you rotate a point?
	Scale(); // Doesn't actually do anything. Why would you scale a point?
	Move();
	Color();

GLPoint
	Render();
	Rotate();
	Scale(); // Will work, but not recomended. Will implement functions for changing the two ends.
	Move();
	Color();

	// Extra functions to make it easier to use
	SetStart(); // Will move the first point in the line
	SetEnd(); // Will move the last point in the line

GLTri
	Render();
	Rotate();
	Scale();
	Move();
	Color();

GLQuad // It's actually just 2 GLTri. Don't tell anyone.
	Render();
	Rotate();
	Scale();
	Move();
	Color();
*/

struct Vertex {
	float position[2], UV[2];
};

// Interface macro for quick declaration of a large block of code.
// Changes here will be automatically updated for any objects using this macro
// REMEMBER TO UPDATE THE OBJECT'S .CPP FILE AS WELL

// Use BASE_GL_PRIMITIVE for the base class and DERIVED_GL_PRIMITIVE for derived classes. DO NOT USE THE INTERFACE DIRECTLY
#define INTERFACE_GL_PRIMITIVE(terminal) \
protected:\
	virtual void Render( void ) ##terminal\
	virtual void Rotate( void ) ##terminal\
	virtual void Scale( void ) ##terminal\
	virtual void Move( void ) ##terminal\
	virtual void Color( void ) ##terminal\

#define BASE_GL_PRIMITIVE		INTERFACE_GL_PRIMITIVE(=0;)
#define DERIVED_GL_PRIMITIVE	INTERFACE_GL_PRIMITIVE(;)

class GLprimitive {

protected:
	glm::vec3 v3_scale, v3_position;
	glm::vec4 v4_color;
	glm::mat4 m4_scale, m4_rotate, m4_move, m4_mvp;
	GLuint shaderProgram, vertexShader, fragmentShader;
	GLint shaderDataAttrib_Position;

public:

	enum GL_PRIMITIVE {
		GLPOINT,
		GLLINE,
		GLTRI,
		GLQUAD, // Actually just 2 triangles, but whatever.
	};

	virtual ~GLprimitive( ) {}

	BASE_GL_PRIMITIVE

};
		

#endif
