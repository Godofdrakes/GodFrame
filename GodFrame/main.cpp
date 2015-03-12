#include <fstream>
#include <iostream>

#include "GodFrame.h"

int main( void ) {

	GameEngine Engine( "GodFrame" ); // Inits the Engine

	/*GLPrimitive * point = Engine.MakeObject( GLPOINT );
	GLPrimitive * tri = Engine.MakeObject( GLTRI );
	point->Move( 500, 500 );
	tri->Move( 200, 200 );*/

	const double TIME_TICKRATE = ( 1.0 / 15 );
	double time_old = Engine.Engine_GetTime( );
	double time_lag = 0.0;

	double foo = 0.0;

	GLuint vao, vbo, ebo;
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

	glm::vec4 v4_color = glm::vec4( 1.f, 1.f, 1.f, 1.f );

	CheckGLError( "main" );

	while( Engine.Window_Update( ) ) {
		double time_now = Engine.Engine_GetTime( );
		double time_passed = time_now - time_old;
		time_old = time_now;
		time_lag += time_passed;

		while( time_lag >= TIME_TICKRATE ) {
			// Do thinking stuff here

			++foo;

			// At the end
			time_lag -= TIME_TICKRATE;
		}

		// Do drawing stuff here
		//object->Rotate( foo );
		/*point->Render( );
		tri->Rotate( (float)foo );
		tri->Render( );*/
		glUseProgram( Engine.shader_Untextured );
		glBindVertexArray( vao );
		glUniformMatrix4fv( glGetUniformLocation( Engine.shader_Untextured, "m4_mvp" ), 1, GL_FALSE, glm::value_ptr( Engine.m4_projection ) );
		glUniform4fv( glGetUniformLocation( Engine.shader_Untextured, "v4_color" ), 1, glm::value_ptr( v4_color ) );
		//glDrawElements( GL_POINTS, 3, GL_UNSIGNED_INT, 0 );
		glDrawArrays( GL_POINTS, 0, 1 );
		CheckGLError( "main2" );

		// if( player pressed ESC ) { Engine.Window_Close( ); }
	}

	/*delete point;
	delete tri;*/

	// Cleanup the windows
	Engine.Window_Close( );
	// Cleanup the engine
	Engine.Engine_Close( );

	return 0;
}