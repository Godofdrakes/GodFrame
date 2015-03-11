#include <fstream>
#include <iostream>

#include "GodFrame.h"

void LoadShader( const char * fileName, GLuint & shaderIndex, GLuint shaderType ) {

	std::ifstream ifs( fileName, std::ios::in | std::ios::binary | std::ios::ate );

	std::ifstream::pos_type fileSize = ifs.tellg( );
	ifs.seekg( 0, std::ios::beg );

	std::vector<char> bytes( fileSize );
	ifs.read( &bytes[0], fileSize );

	std::string sourceCode( bytes.begin( ), bytes.end( ) );

	const GLchar* sourceChars = sourceCode.c_str( );

	shaderIndex = glCreateShader( shaderType ); // What kind of shader is it?
	glShaderSource( shaderIndex, 1, &sourceChars, NULL ); // Load the code for the shader
	glCompileShader( shaderIndex ); // Build the shader from that code

	// Error checking
	GLint isCompiled = 0;
	glGetShaderiv( shaderIndex, GL_COMPILE_STATUS, &isCompiled );

#ifdef _DEBUG
	char buffer[512];
	glGetShaderInfoLog( shaderIndex, 512, NULL, buffer );
	std::cout << buffer << std::endl;
#endif

	assert( isCompiled = GL_TRUE && "| LoadShader - Could not compile shader |" );
}

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

	GameEngine Engine; // Inits the Engine

	GLTri point;

	LoadShader( "engine/shader/Shader_Vertex_NOTEXTURE.glsl", point.shader_Vertex, GL_VERTEX_SHADER );
	LoadShader( "engine/shader/Shader_Fragment_NOTEXTURE.glsl", point.shader_Fragment, GL_FRAGMENT_SHADER );
	LoadShaderProgramNOTEXTURE( point );
	glm::mat4 proj = glm::ortho( 0.f, (float)1024, (float)768, 0.f );

	
	point.Move( 100, 100 );
	point.SetMVP( proj );

	const double TIME_TICKRATE = ( 1.0 / 30.0 );
	double time_old = Engine.Engine_GetTime( );
	double time_lag = 0.0;

	while( Engine.Update( ) ) {
		double time_now = Engine.Engine_GetTime( );
		double time_passed = time_now - time_old;
		time_old = time_now;
		time_lag += time_passed;

		while( time_lag >= TIME_TICKRATE ) {
			// Do thinking stuff here

			// At the end
			time_lag -= TIME_TICKRATE;
		}

		// Do drawing stuff here
		point.Render( );

		// if( player pressed ESC ) { Engine.Window_Close( ); }
	}

	// Cleanup the windows
	Engine.Window_Close( );
	// Cleanup the engine
	Engine.Engine_Close( );

	return 0;
}