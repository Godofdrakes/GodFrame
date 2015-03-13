#include "GodFrame.h"
#include <assert.h>
#include <fstream>
#include <vector>

GameEngine::GameEngine( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) {
	error_glfw = !( glfwInit( ) == GL_TRUE ); // Returns GL_TRUE if all is well.
	assert( !error_glfw && "| GameEngine::StartUp - glfw Could not initialize |" );

	glfwSetErrorCallback( error_callback );
	windowPointer = NULL;

	Window_New( windowName, windowWidth, windowHeight );
	m4_projection = glm::ortho( 0.f, (float)windowWidth, 0.f, (float)windowHeight );

	error_glew = !( glewInit( ) == GLEW_OK );
	assert( !error_glew && "| GameEngine::StartUp - glew Could not initialize |" );

	Shader_Load( "engine/shader/Shader_Vertex_TEXTURE.glsl", textured.vertex, GL_VERTEX_SHADER );
	Shader_Load( "engine/shader/Shader_Fragment_TEXTURE.glsl", textured.fragment, GL_FRAGMENT_SHADER );
	Shader_Link( textured.handle, textured.vertex, textured.fragment, true );

	Shader_Load( "engine/shader/Shader_Vertex_NOTEXTURE.glsl", untextured.vertex, GL_VERTEX_SHADER );
	Shader_Load( "engine/shader/Shader_Fragment_NOTEXTURE.glsl", untextured.fragment, GL_FRAGMENT_SHADER );
	Shader_Link( untextured.handle, untextured.vertex, untextured.fragment, false );;
}
void GameEngine::Shader_Load( const char * fileName, GLuint & shaderIndex, GLuint shaderType ) {
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

	if( isCompiled != GL_TRUE ) {
#ifdef _DEBUG
		char buffer[512];
		glGetShaderInfoLog( shaderIndex, 512, NULL, buffer );
		assert( buffer );
#else
		assert( "| LoadShader - Could not compile shader |" );
#endif
	}
}
void GameEngine::Shader_Link( GLuint & shader_program, GLuint & shader_vertex, GLuint & shader_fragment, bool textured ) {
	shader_program = glCreateProgram( ); // Create the program
	glAttachShader( shader_program, shader_vertex ); // Load the shaders to it.
	glAttachShader( shader_program, shader_fragment );

	// A fragment shader can have multiple buffers so we need to tell it which output is written where.
	glBindFragDataLocation( shader_program, 0, "v4_outColor" );

	// Now we have to link the program.
	glLinkProgram( shader_program );

	GLint isLinked = 0;
	glGetProgramiv( shader_program, GL_LINK_STATUS, &isLinked );
	if( isLinked == GL_FALSE ) {
		GLint maxLength = 0;
		glGetProgramiv( shader_program, GL_INFO_LOG_LENGTH, &maxLength );

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog( maxLength );
		glGetProgramInfoLog( shader_program, maxLength, &maxLength, &infoLog[0] );

		//The program is useless now. So delete it.
		glDeleteProgram( shader_program );

		//Provide the infolog in whatever manner you deem best.
		//Exit with failure.
		return;
	}

	// To actually use the sahders we have to say we are using the program.
	glUseProgram( shader_program );
	// Only one program can be active at a time.

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	GLuint shaderDataAttrib_Position = glGetAttribLocation( shader_program, "v2_position" );
	glEnableVertexAttribArray( shaderDataAttrib_Position );
	glVertexAttribPointer( shaderDataAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	if( textured ) {
		GLuint shaderDataAttrib_Position = glGetAttribLocation( shader_program, "v2_texcoord" );
		glEnableVertexAttribArray( shaderDataAttrib_Position );
		glVertexAttribPointer( shaderDataAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	}
}

void GameEngine::Window_New( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	assert( windowPointer == NULL && "| GameEngine::NewWindow - windowPointer already exists |" );
	assert( windowName && "| GameEngine::NewWindow - Invalid window name |" );
	assert( windowWidth > 0 && "| GameEngine::NewWindow - width must be greater than 0 |" );
	assert( windowHeight > 0 && "| GameEngine::NewWindow - hieght must be greater than 0 |" );

	// Set window privates
	name = std::string( windowName );
	width = windowWidth;
	height = windowHeight;

	// Init window
	windowPointer = glfwCreateWindow( width, height, name.c_str( ), NULL, NULL );
	assert( windowPointer != NULL && "| GameEngine::NewWindow - GLFW returned NULL pointer for windowPointer |" );

	// Default the window color to black.
	color[0] = 0.f; color[1] = 0.f; color[2] = 0.f; color[3] = 1.f;

	glfwMakeContextCurrent( windowPointer );
	glfwSwapInterval( 1 );
}

bool GameEngine::Window_Update( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	assert( windowPointer != NULL && "| GameEngine::Update - windowPointer is NULL |" );

	if( glfwWindowShouldClose( windowPointer ) ) { return false; }

	// Stuff for the end of this tick.
	glfwSwapBuffers( windowPointer );
	glfwPollEvents( );

	// Stuff for the start of the next tick.
	glClearColor( color[0], color[1], color[2], color[3] );
	glClear( GL_COLOR_BUFFER_BIT );

	return true;
}
void GameEngine::Window_Stop( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	assert( windowPointer != NULL && "| GameEngine::EndWindow - windowPointer is NULL |" );
	return glfwSetWindowShouldClose( windowPointer, GL_FALSE ); // Tell the window it's no longer needed
}
void GameEngine::Window_Close( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	assert( windowPointer != NULL && "| GameEngine::CloseWindow - windowPointer is NULL |" );
	glfwDestroyWindow( windowPointer ); // Close the window
	windowPointer = NULL; // We don't need the pointer any more
}

const char* GameEngine::Window_GetName( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	return name.c_str( );
}
int GameEngine::Window_GetWidth( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	return width;
}
int GameEngine::Window_GetHeight( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	return height;
}

void GameEngine::Engine_Close( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	// Technically I should be deleting shaders.
	glfwTerminate( ); // Shut down all the things! ALL THE THINGS!
}
double GameEngine::Engine_GetTime( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	return glfwGetTime( );
}
void GameEngine::Engine_SetBackgroundColor( float r, float g, float b, float a ) {
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}
GLPrimitive * GameEngine::MakeObject( GL_PRIMITIVE type ) {
	GLPrimitive * object = NULL;
	switch( type ) {
	case GLPOINT:
		object = new GLPoint( untextured.handle, m4_projection );
		break;
	case GLLINE:
		object = new GLPoint( untextured.handle, m4_projection );
		break;
	case GLTRI:
		object = new GLTri( untextured.handle, m4_projection );
		break;
	default:
		assert( "| GameEngine::MakeObject - invalid type |" );
		break;
	}
	return object;
}