#include <fstream>
#include <iostream>

#include "GodFrame.h"

void LoadShaderProgramNOTEXTURE( GLPrimitive & glObject ) {
	glObject.shader_Program = glCreateProgram( ); // Create the program
	glAttachShader( glObject.shader_Program, glObject.shader_Vertex ); // Load the shaders to it.
	glAttachShader( glObject.shader_Program, glObject.shader_Fragment );

	// A fragment shader can have multiple buffers so we need to tell it which output is written where.
	glBindFragDataLocation( glObject.shader_Program, 0, "v4_outColor" );

	//glTransformFeedbackVaryings( glObject.shader_Program, 1, glObject.feedBack, GL_INTERLEAVED_ATTRIBS );

	// Now we have to link the program.
	glLinkProgram( glObject.shader_Program );

	GLint isLinked = 0;
	glGetProgramiv( glObject.shader_Program, GL_LINK_STATUS, &isLinked );
	assert( isLinked = GL_TRUE && "| LoadShaderProgramNOTEXTURE - Could not link shader program |" );

	// To actually use the sahders we have to say we are using the program.
	glUseProgram( glObject.shader_Program );
	// Only one program can be active at a time.

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glObject.shaderDataAttrib_Position = glGetAttribLocation( glObject.shader_Program, "v2_position" );
	glEnableVertexAttribArray( glObject.shaderDataAttrib_Position );
	glVertexAttribPointer( glObject.shaderDataAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0 );
}

int main( void ) {

	GameEngine Engine( "GodFrame" ); // Inits the Engine

	RenderObject point = ;

	const double TIME_TICKRATE = ( 1.0 / 15 );
	double time_old = Engine.Engine_GetTime( );
	double time_lag = 0.0;

	float foo = 0.f;

	while( Engine.Window_Update( ) ) {
		double time_now = Engine.Engine_GetTime( );
		double time_passed = time_now - time_old;
		time_old = time_now;
		time_lag += time_passed;

		while( time_lag >= TIME_TICKRATE ) {
			// Do thinking stuff here

			foo += 0.5;

			// At the end
			time_lag -= TIME_TICKRATE;
		}

		// Do drawing stuff here
		point.SetMVP( Engine.m4_projection );
		point.Render( );

		// if( player pressed ESC ) { Engine.Window_Close( ); }
	}

	// Cleanup the windows
	Engine.Window_Close( );
	// Cleanup the engine
	Engine.Engine_Close( );

	return 0;
}