#include "../include/GLpoint.h"

void GLpoint::GenBuffers( void ) {
	// No texture
	glGenVertexArrays( 1, &vao );
	glGenBuffers( 1, &vbo );
	// No UV data
	glGenBuffers( 1, &ebo );
}
void GLpoint::DestroyBuffers( void ) {
	// No texture
	glDeleteVertexArrays( 1, &vao );
	glDeleteBuffers( 1, &vbo );
	// No UV data
	glDeleteBuffers( 1, &ebo );
}

void GLpoint::BindBuffers( void ) {
	// No texture
	glBindVertexArray( vao );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	// No UV data
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
}
void GLpoint::BufferVBO( void ) {
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( data_vertex ) * 4, data_vertex, GL_DYNAMIC_DRAW );
}
void GLpoint::BufferUVO( void ) {
	// No UV data
}
void GLpoint::BufferEBO( void ) {
	GLuint elements[] = {
		0, 1, 2,
		2, 3, 1,
	};

	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_DYNAMIC_DRAW );
}

void GLpoint::LoadTexture( const char* fileName ) {
	// No texture
}

void GLpoint::SetSize( float set_width, float set_height ) {
	// Do nothing. A point has no size
	model = glm::mat4( 1.f ); // Identity matrix
}
void GLpoint::SetSize( glm::vec2 set_size ) {
	// Do nothing. A point has no size
	model = glm::mat4( 1.f ); // Identity matrix
}

void GLpoint::SetPosition( float set_x, float set_y ) {
	position = glm::vec3( set_x, set_y, 1.f );
	view = glm::translate( glm::mat4( ), position );
}
void GLpoint::SetPosition( glm::vec2 set_position ) {
	position = glm::vec3( set_position, 1.f );
	view = glm::translate( glm::mat4( ), position );
}

void GLpoint::SetColor( float set_red, float set_green, float set_blue, float set_alpha ) {
	color = glm::vec4( set_red, set_green, set_blue, set_alpha );
}
void GLpoint::SetColor( glm::vec4 set_color ) {
	color = set_color;
}

void GLpoint::SetRotaionRad( float radians ) {
	rotation = glm::rotate( glm::mat4( ), radians, glm::vec3( 0.f, 0.f, 1.f ) );
}
void GLpoint::SetRotaionDeg( float degrees ) {
	SetRotaionRad( degrees * ( 3.14159 * 180 ) );
}

void GLpoint::SetMVP( glm::mat4 projection ) {
	mvp = projection * view * rotation * model;
}

void GLpoint::Draw( void ) {

}