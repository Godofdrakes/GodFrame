#include "../include/GodFrame.h"

GameEngine::GameEngine( void ) {
	int glfwInitError = glfwInit( );
	assert( glfwInitError == GL_TRUE && "GameEngine::StartUp - glfwInit returned GL_FALSE" );

	glfwSetErrorCallback( error_callback );
	windowPointer = NULL;
}

void GameEngine::NewWindow( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) {
	assert( windowPointer == NULL && "GameEngine::NewWindow - windowPointer already exists" );
	assert( windowName && "GameEngine::NewWindow - Invalid windowName" );
	assert( windowWidth > 0 && "GameEngine::NewWindow - width <= 0" );
	assert( windowHeight > 0 && "GameEngine::NewWindow - hieght <=0" );

	name = std::string( windowName );
	width = windowWidth;
	height = windowHeight;

	windowPointer = glfwCreateWindow( width, height, name.c_str( ), NULL, NULL );
	assert( windowPointer != NULL && "GameEngine::NewWindow - GLFW returned NULL pointer for windowPointer" );

	glfwMakeContextCurrent( windowPointer );
	glfwSwapInterval( 1 );

}

void GameEngine::EndWindow( ) {
	assert( windowPointer != NULL && "GameEngine::EndWindow - windowPointer is NULL" );
	return glfwSetWindowShouldClose( windowPointer, GL_FALSE );
}

void GameEngine::CloseWindow( ) {
	assert( windowPointer != NULL && "GameEngine::CloseWindow - windowPointer is NULL" );
	glfwDestroyWindow( windowPointer );
	windowPointer = NULL;
}

void GameEngine::ShutDown( void ) {
	glfwTerminate( );
}

double GameEngine::GetDeltaTime( ) {
	return glfwGetTime( );
}

bool GameEngine::Update( ) {
	assert( windowPointer != NULL && "GameEngine::Update - windowPointer is NULL" );

	if( glfwWindowShouldClose( windowPointer ) ) { return false; }

	glfwSwapBuffers( windowPointer );
	glfwPollEvents( );

	deltaTime = glfwGetTime( );
	glfwSetTime( 0 );

	return true;
}