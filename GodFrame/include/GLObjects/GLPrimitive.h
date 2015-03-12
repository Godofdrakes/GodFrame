#ifndef _GLPRIMITIVE_H_
#define _GLPRIMITIVE_H_

#include "../OpenGL_Tools.h"
#include "../GLM_Tools.h"

/* Overall object planning

Couldn't get abstraction working quite correctly.

Four seperate objects?

Main contains framework
	Framework contains Object factory

Main calls Framework
	Framework calls Factory
		Factory makes Object
		Factory returns Object
	Framework returns Object
Main gets Object

*/

/* GLPrimitive base/derived planning

GLPrimitive
	Render() = 0; // The code that actualls calls the GL functions to draw.
	Rotate( float radians ) = 0; // Updates the rotation matrix
	Scale( float scale_x, float scale_y ) = 0; // Updates the scale matrix
	Move( float move_X, float move_y ) = 0; // Updates the move matrix
	Color( float color_r, float color_g, float color_b, float color_a ) = 0; // Updates the color vector


GLLine
	// For ease of use, have the line's verts be in center and to the right.
	// This results in the line's 'center' being the start of the line.
	// Just set the line's width to how long it needs to be and you're good.

	Render();
	Rotate( float radians );
	Scale( float scale_x, float scale_y ); // Will work, but not recomended. Will implement functions for changing the two ends.
	Move( float move_X, float move_y );
	Color( float color_r, float color_g, float color_b, float color_a );


GLTri
	Render();
	Rotate( float radians );
	Scale( float scale_x, float scale_y );
	Move( float move_X, float move_y );
	Color( float color_r, float color_g, float color_b, float color_a );


GLQuad // It's actually just 2 GLTri. Don't tell anyone.
	Render();
	Rotate( float radians );
	Scale( float scale_x, float scale_y );
	Move( float move_X, float move_y );
	Color( float color_r, float color_g, float color_b, float color_a );

*/

struct Vertex {
	float data[2];
};

// Interface macro for quick declaration of a large block of code.
// Changes here will be automatically updated for any objects using this macro
// REMEMBER TO UPDATE THE OBJECT'S .CPP FILE AS WELL

// Use BASE_GL_PRIMITIVE for the base class and DERIVED_GL_PRIMITIVE for derived classes. DO NOT USE THE INTERFACE DIRECTLY
#define INTERFACE_GL_PRIMITIVE(terminal) \
public:\
	virtual void Render( void ) ##terminal\
	virtual void Rotate( float radians ) ##terminal\
	virtual void Scale( float scale_x, float scale_y ) ##terminal\
	virtual void Move( float move_X, float move_y ) ##terminal\
	virtual void Color( float color_r, float color_g, float color_b, float color_a ) ##terminal\

#define BASE_GL_PRIMITIVE		INTERFACE_GL_PRIMITIVE(=0;)
#define DERIVED_GL_PRIMITIVE	INTERFACE_GL_PRIMITIVE(;)


enum GL_PRIMITIVE {
	GLPOINT,
	GLLINE,
	GLTRI,
	GLQUAD, // Actually just 2 triangles, but whatever.
};

class GLPrimitive {

protected:
	glm::vec4 v4_color;
	glm::mat4 m4_scale, m4_rotate, m4_move, m4_mvp, m4_projection;
	GLuint shader_Program;
	GLuint vao, vbo, ebo;

public:
	//GLint shaderDataAttrib_Position;

	virtual ~GLPrimitive( ) {}

	BASE_GL_PRIMITIVE

};	

#endif
