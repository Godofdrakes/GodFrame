#ifndef _GLOBJECTMANAGER_H_
#define _GLOBJECTMANAGER_H_

/* Planning

store points, lines, tris, and quads
store two shaders (textured/non-textured)
store the projection

load shaders from file
make shaderprogram from shaders
return an object that can be used to draw ( week reference? )

*/

#include "OpenGL_Tools.h"
#include "GLM_Tools.h"
#include "GLObjects.h"

class ShaderProgram {

private:
	GLuint shader_Vertex, shader_Fragment;

	void LoadShader( const char * fileName, GLuint & shaderIndex, GLuint shaderType );
	void LinkShader( GLuint shader_program, GLuint shader_vertex, GLuint shader_fragment, bool textured );

public:
	GLuint shader_Program;

	ShaderProgram( void );
	ShaderProgram( const char * filePath_vertexShader, const char * filePath_fragmentShaderm, bool useTextures );
	~ShaderProgram( void );

	ShaderProgram & operator=( ShaderProgram & other );

};

class GLPrimitive;

class RenderObject {

private:
	GLPrimitive * glObject;
	GLuint shader;
	glm::mat4 mvp;

public:
	RenderObject( void );
	RenderObject( const RenderObject & other );
	RenderObject( GLPrimitive * object, GLuint shaderHandle, glm::mat4 set_mvp );

	void Render( void );
	void Rotate( float radians );
	void Scale( float scale_x, float scale_y );
	void Move( float move_X, float move_y );
	void Color( float color_r, float color_g, float color_b, float color_a );

	RenderObject & operator=( const RenderObject & other ) {
		glObject = other.glObject;
		shader = other.shader;
		mvp = other.mvp;
	}

};

class RenderObjectManager {

private:
	ShaderProgram shaderProgram_UNTEXTURED, ShaderProgram_TEXTURED;
	glm::mat4 projection;

public:
	RenderObjectManager( void );
	RenderObjectManager( glm::mat4 set_projection );

	void SetProjection( glm::mat4 set_projection );

	RenderObjectManager & operator=( RenderObjectManager & other );
	RenderObjectManager & MakeObject( GL_PRIMITIVE type );

};

#endif
