#include "GodFrame.h"
#include <assert.h>
#include <fstream>
#include <vector>

bool GameEngine::engineHasStarted = false;
unsigned int GameEngine::width = 0, GameEngine::height = 0;
float GameEngine::color[4] = { 0.f, 0.f, 0.f, 1.f }; // Color of the window's background
GLFWwindow * GameEngine::windowPointer = NULL; // Pointer to the window
std::string GameEngine::name; // Name of the window
glm::mat4 GameEngine::m4_projection = glm::mat4( 1.f );
ShaderProgram GameEngine::textured, GameEngine::untextured;
BMFont GameEngine::fontManager;
Input_Mouse GameEngine::mouseInput;
Input_Keyboard GameEngine::keyboardInput;
bool GameEngine::drawFPS;
double GameEngine::delta_new, GameEngine::delta_old;

GameEngine::GameEngine( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) {

	assert( engineHasStarted == false && "An instance of GameEngine already exists" );

	bool error_glfw = !( glfwInit( ) == GL_TRUE ); // Returns GL_TRUE if all is well.
	assert( !error_glfw && "| GameEngine::StartUp - glfw Could not initialize |" );

	glfwSetErrorCallback( error_callback );
	windowPointer = NULL;

	Window_New( windowName, windowWidth, windowHeight );
	m4_projection = glm::ortho( 0.f, (float)windowWidth, 0.f, (float)windowHeight );

	GLenum error_glew = !( glewInit( ) == GLEW_OK );
	assert( !error_glew && "| GameEngine::StartUp - glew Could not initialize |" );

	Shader_Load( "engine/shader/Shader_Vertex_TEXTURE.glsl", textured.vertex, GL_VERTEX_SHADER );
	Shader_Load( "engine/shader/Shader_Fragment_TEXTURE.glsl", textured.fragment, GL_FRAGMENT_SHADER );
	Shader_Link( textured.handle, textured.vertex, textured.fragment, true );

	Shader_Load( "engine/shader/Shader_Vertex_NOTEXTURE.glsl", untextured.vertex, GL_VERTEX_SHADER );
	Shader_Load( "engine/shader/Shader_Fragment_NOTEXTURE.glsl", untextured.fragment, GL_FRAGMENT_SHADER );
	Shader_Link( untextured.handle, untextured.vertex, untextured.fragment, false );

	drawFPS = false;
	delta_new = glfwGetTime( );
	delta_old = 0.0;
	engineHasStarted = true;
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
		char buffer[512];
		glGetShaderInfoLog( shaderIndex, 512, NULL, buffer );
		assert( "Could not compile shader" && buffer );
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
	assert( windowName && "| GameEngine::NewWindow - Invalid window name |" );
	assert( windowWidth > 0 && "| GameEngine::NewWindow - width must be greater than 0 |" );
	assert( windowHeight > 0 && "| GameEngine::NewWindow - hieght must be greater than 0 |" );

	// Set window privates
	name = std::string( windowName );
	width = windowWidth;
	height = windowHeight;

	// Init window
	windowPointer = glfwCreateWindow( width, height, name.c_str( ), NULL, NULL );
	assert( windowPointer != NULL && "windowPointer == NULL" );

	// Default the window color to black.
	color[0] = 0.f; color[1] = 0.f; color[2] = 0.f; color[3] = 1.f;

	glfwMakeContextCurrent( windowPointer );
	glfwSwapInterval( 1 );
}

void GameEngine::ShowFPS( void ) {
	if( !drawFPS ) { return; }
	if( !fontManager.numPages ) { return; }

	delta_old = delta_new;
	delta_new = glfwGetTime( );
	double delta = delta_new - delta_old;

	float fontsize = fontManager.fontScale;
	fontManager.FontScale( 25.f );

	std::stringstream temp;
	temp << "FPS: " << (int)( 1.f / delta );
	fontManager.DrawString( temp.str( ).c_str( ), 0, 0 );

	fontManager.fontScale = fontsize;
}

bool GameEngine::Window_Update( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine already exists" );
	assert( windowPointer != NULL && "windowPointer == NULL" );

	if( glfwWindowShouldClose( windowPointer ) ) { return false; }

	// Stuff for the end of this tick.
	ShowFPS( );
	glfwSwapBuffers( windowPointer );
	glfwPollEvents( );

	// Stuff for the start of the next tick.
	glClearColor( color[0], color[1], color[2], color[3] );
	glClear( GL_COLOR_BUFFER_BIT );

	return true;
}
void GameEngine::Window_Stop( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	assert( windowPointer != NULL && "windowPointer == NULL" );
	return glfwSetWindowShouldClose( windowPointer, GL_TRUE ); // Tell the window it's no longer needed
}
void GameEngine::Window_Close( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	assert( windowPointer != NULL && "windowPointer == NULL" );
	glfwDestroyWindow( windowPointer ); // Close the window
	windowPointer = NULL; // We don't need the pointer any more
}

const char* GameEngine::Window_GetName( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	return name.c_str( );
}
int GameEngine::Window_GetWidth( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	return width;
}
int GameEngine::Window_GetHeight( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	return height;
}

void GameEngine::Engine_Close( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	// Technically I should be deleting shaders.
	fontManager.UnloadFont( );
	glfwTerminate( ); // Shut down all the things! ALL THE THINGS!
}
double GameEngine::Engine_GetTime( void ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	return glfwGetTime( );
}
void GameEngine::Engine_SetBackgroundColor( float r, float g, float b, float a ) {
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}

void GameEngine::Input_MousePos( double & mouse_x, double & mouse_y ) {
	mouseInput.GetMousePos( windowPointer, mouse_x, mouse_y );
	mouse_y = height - mouse_y;
}
bool GameEngine::Input_MouseButton( int button ) {
	return mouseInput.GetMouseButton( windowPointer, button );
}
bool GameEngine::Input_KeyboardButton( int button ) {
	return keyboardInput.GetKeyboardButton( windowPointer, button );
}

GLPrimitive * GameEngine::MakeObject( GL_PRIMITIVE type, const char * optional_textureFilePath ) {
	assert( engineHasStarted == true && "No instance of GameEngine exists" );
	GLPrimitive * object = NULL;
	switch( type ) {
	case GLPOINT:
		object = new GLPoint( untextured.handle, m4_projection );
		break;
	case GLLINE:
		object = new GLLine( untextured.handle, m4_projection );
		break;
	case GLTRI:
		object = new GLTri( untextured.handle, m4_projection );
		break;
	case GLQUAD:
		object = new GLQuad( untextured.handle, m4_projection );
		break;
	case GLTEXTURE:
		assert( optional_textureFilePath != NULL && "Must provide file path to texture" );
		object = new GLTexture( textured.handle, m4_projection, optional_textureFilePath );
		break;
	default:
		assert( "| GameEngine::MakeObject - invalid type |" );
		break;
	}
	return object;
}
void GameEngine::LoadFont( const char * fontFilePath ) {
	fontManager.LoadFont( fontFilePath, textured.handle, m4_projection );
}