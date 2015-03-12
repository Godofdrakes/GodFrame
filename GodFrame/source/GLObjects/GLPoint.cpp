#include "GLObjects/GLPoint.h"
#include "OpenGL_Tools.h"

GLPoint::GLPoint( GLuint shader, glm::mat4 projection ) {
	CheckGLError( "GLPoint::GLPoint - start" );
	shader_Program = shader;
	m4_mvp = m4_move = m4_rotate = m4_scale = glm::mat4( 1.f );
	m4_projection = projection;

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	float vertices[] = { 0.0f, 0.0f };

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	GLuint elements[] = { 0 };

	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	Color( 1.f, 1.f, 1.f, 1.f );
	CheckGLError( "GLPoint::GLPoint - end" );
}
GLPoint::~GLPoint( void ) {
	CheckGLError( "GLPoint::~GLPoint - start" );
	glDeleteBuffers( 1, &ebo );
	glDeleteBuffers( 1, &vbo );
	glDeleteVertexArrays( 1, &vao );
	CheckGLError( "GLPoint::~GLPoint - end" );
}
void GLPoint::Render( void ) {
	CheckGLError( "GLPoint::Render - start" );

	m4_mvp = m4_projection * m4_move * m4_rotate * m4_scale;

	glUseProgram( shader_Program );
	glBindVertexArray( vao );

	glUniformMatrix4fv( glGetUniformLocation( shader_Program, "m4_mvp" ), 1, GL_FALSE, glm::value_ptr( m4_mvp ) );
	glUniform4fv( glGetUniformLocation( shader_Program, "v4_color" ), 1, glm::value_ptr( v4_color ) );

	glDrawElements( GL_POINTS, 1, GL_UNSIGNED_INT, 0 );

	CheckGLError( "GLPoint::Render - end" );
}
void GLPoint::Rotate( float radians ) {
	m4_rotate = glm::rotate( glm::mat4( ), radians, glm::vec3( 0.f, 0.f, 1.f ) );
}
void GLPoint::Scale( float scale_x, float scale_y ) {
	glm::vec3 v3_scale = glm::vec3( scale_x, scale_y, 1.f );
	m4_scale = glm::scale( glm::mat4( ), v3_scale );
}
void GLPoint::Move( float move_X, float move_y ) {
	glm::vec3 v3_position = glm::vec3( move_X, move_y, 1.f );
	m4_move = glm::translate( glm::mat4( ), v3_position );
}
void GLPoint::Color( float color_r, float color_g, float color_b, float color_a ) {
	v4_color = glm::vec4( color_r, color_g, color_b, color_a );
}