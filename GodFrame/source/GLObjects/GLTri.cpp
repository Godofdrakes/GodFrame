#include "GLObjects.h"

GLTri::GLTri( void ) {
	glPrim = GLTRI;

	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );

	float vertices[] = {
		0.0f, 0.5f,
		0.5f, -0.5f,
		-0.5f, -0.5f,
	};

	glGenBuffers( 1, &vbo );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	GLuint elements[] = { 0, 1, 2 };

	glGenBuffers( 1, &ebo );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

	Scale( 64.f, 64.f );
	Move( 64.f, 64.f );
	Color( 1.f, 1.f, 1.f, 1.f );
}
GLTri::~GLTri( void ) {
	glDeleteBuffers( 1, &ebo );
	glDeleteBuffers( 1, &vbo );
	glDeleteVertexArrays( 1, &vao );
}
void GLTri::Render( GLuint & shader ) {
	glUseProgram( shader );
	glBindVertexArray( vao );

	glUniformMatrix4fv( glGetUniformLocation( shader, "m4_mvp" ), 1, GL_FALSE, glm::value_ptr( m4_mvp ) );
	glUniform4fv( glGetUniformLocation( shader, "v4_color" ), 1, glm::value_ptr( v4_color ) );

	glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
}
void GLTri::Rotate( float radians ) {
	m4_rotate = glm::rotate( glm::mat4( ), radians, glm::vec3( 0.f, 0.f, 1.f ) );
}
void GLTri::Scale( float scale_x, float scale_y ) {
	glm::vec3 v3_scale = glm::vec3( scale_x, scale_y, 1.f );
	m4_scale = glm::scale( glm::mat4( ), v3_scale );
}
void GLTri::Move( float move_X, float move_y ) {
	glm::vec3 v3_position = glm::vec3( move_X, move_y, 1.f );
	m4_move = glm::translate( glm::mat4( ), v3_position );
}
void GLTri::Color( float color_r, float color_g, float color_b, float color_a ) {
	v4_color = glm::vec4( color_r, color_g, color_b, color_a );
}
void GLTri::SetMVP( glm::mat4 projection ) {
	m4_mvp = projection * m4_move * m4_rotate * m4_scale;
}