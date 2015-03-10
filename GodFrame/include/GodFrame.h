#ifndef _GODFRAME_H_
#define _GODFRAME_H_

#include <assert.h>
#include <string>
#include "OpenGL_Tools.h" // GLEW, GLFW, GLM
#include <RapidXML\rapidxml.hpp>

/*

function ErrorCallback( int error, const char* description )
	assert( 0 && description )

class Window
	glfwWindowPointer windowPointer

	constructor( string windowName, unsigned int width, unsigned int height )
		assert( windowName && "Window::Window - Invalid windowName" )
		assert( width > 0 && "Window::Window - width <= 0" )
		assert( height > 0 && "Window::Window - hieght <=0" )

		windowPointer = glfwCreateWindow( width, height, windowName, NULL, NULL )
		assert( windowPointer != NULL && "Window::Window - GLFW returned NULL pointer for windowPointer" )

		glfwMakeContextCurrent( windowPointer )
		glfwSwapInterval(1);

	function MakeActive()
		glfwMakeContextCurrent( windowPointer )

	function ShouldClose( Window& )
		assert( windowPointer != NULL && "Window::ShouldClose - windowPointer is NULL" )
		return glfwWindowShouldClose( windowPointer )

	function CloseWindow( Window& )
		assert( windowPointer != NULL && "Window::CloseWindow - windowPointer is NULL" )
		return glfwSetWindowShouldClose( windowPointer, GL_FALSE )

	// destructor?
	function CleanupWindow( Window& )
		assert( windowPointer != NULL && "Window::CleanupWindow - windowPointer is NULL" )
		glfwDestroyWindow( windowPointer )

	function Update()
		assert( windowPointer != NULL && "Window::Update - windowPointer is NULL" )
		glfwSwapBuffers( windowPointer )
		
	

class GameEngine
	// Make this the constructor?
	friend function StartUp()
		bool glfwInitError = glfwInit();
		assert( glfwInitError == GL_TRUE && "Framework::StartUp - glfwInit returned GL_FALSE" )

		glfwSetErrorCallback( error_callback )

	// Make this the destructor?
	function Shutdown()
		glfwTerminate()

	function GetDeltaTime()
		return glfwGetTime()

	function Update()
		glfwPollEvents()

*/

// Function for GLFW error handling. Not recomended for actual use.
static void error_callback( int error, const char* description ) { assert( 0 && description ); }

class GameEngine {

private:
	GLFWwindow * windowPointer;
	unsigned int width, height;
	std::string name;

public:
	double deltaTime;

	GameEngine( void ) {
		int glfwInitError = glfwInit( );
		assert( glfwInitError == GL_TRUE && "GameEngine::StartUp - glfwInit returned GL_FALSE" );

		glfwSetErrorCallback( error_callback );
		windowPointer = NULL;
	}

	void NewWindow( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) {
		assert( windowPointer == NULL && "GameEngine::NewWindow - windowPointer already exists" );
		assert( windowName && "GameEngine::NewWindow - Invalid windowName" );
		assert( windowWidth > 0 && "GameEngine::NewWindow - width <= 0" );
		assert( windowHeight > 0 && "GameEngine::NewWindow - hieght <=0" );

		name = std::string( windowName );
		width = windowWidth;
		height = windowHeight;

		windowPointer = glfwCreateWindow( width, height, name.c_str(), NULL, NULL );
		assert( windowPointer != NULL && "GameEngine::NewWindow - GLFW returned NULL pointer for windowPointer" );

		glfwMakeContextCurrent( windowPointer );
		glfwSwapInterval( 1 );

	}

	void EndWindow( ) {
		assert( windowPointer != NULL && "GameEngine::EndWindow - windowPointer is NULL" );
		return glfwSetWindowShouldClose( windowPointer, GL_FALSE );
	}

	void CloseWindow( ) {
		assert( windowPointer != NULL && "GameEngine::CloseWindow - windowPointer is NULL" );
		glfwDestroyWindow( windowPointer );
		windowPointer = NULL;
	}

	// Make this the destructor?
	void ShutDown( void ) {
		glfwTerminate( );
	}

	double GetDeltaTime( ) {
		return glfwGetTime( );
	}

	bool Update( ) {
		assert( windowPointer != NULL && "GameEngine::Update - windowPointer is NULL" );

		if( glfwWindowShouldClose( windowPointer ) ) { return false; }

		glfwSwapBuffers( windowPointer );
		glfwPollEvents( );

		deltaTime = glfwGetTime( );
		glfwSetTime( 0 );

		return true;
	}

};

#endif
