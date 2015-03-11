#include "GodFrame.h"
#include <assert.h>

GameEngine::GameEngine( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) {
	error_glfw = !( glfwInit( ) == GL_TRUE ); // Returns GL_TRUE if all is well.
	assert( !error_glfw && "| GameEngine::StartUp - glfw Could not initialize |" );

	glfwSetErrorCallback( error_callback );
	windowPointer = NULL;

	Window_New( windowName, windowWidth, windowHeight );
	m4_projection = glm::ortho( 0.f, (float)windowWidth, 0.f, (float)windowHeight );

	error_glew = !( glewInit( ) == GLEW_OK );
	assert( !error_glew && "| GameEngine::StartUp - glew Could not initialize |" );

	renderObjectmanager = RenderObjectManager( m4_projection );
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
	glfwTerminate( ); // Shut down all the things! ALL THE THINGS!
}
double GameEngine::Engine_GetTime( void ) {
	assert( !error_glew && "| GameEngine::StartUp - glfw Could not initialize |" );
	return glfwGetTime( );
}
void GameEngine::Engine_SetBackgroundColor( float r, float g, float b, float a ) {
	color[0] = r; color[1] = g; color[2] = b; color[3] = a;
}

RenderObject & GameEngine::MakeObject( GL_PRIMITIVE type ) {

}