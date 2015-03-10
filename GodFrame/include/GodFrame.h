#ifndef _GODFRAME_H_
#define _GODFRAME_H_

#include <assert.h>
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

class Window {

private:
	GLFWwindow * windowPointer;
	const unsigned int width, height;
	const char* name;

public:

	Window( const char* windowName, unsigned int windowWidth, unsigned int windowHeight ) : name(windowName), width(windowWidth), height(windowHeight) {
		assert( name && "Window::Window - Invalid windowName" );
		assert( width > 0 && "Window::Window - width <= 0" );
		assert( height > 0 && "Window::Window - hieght <=0" );

		windowPointer = glfwCreateWindow( width, height, name, NULL, NULL );
		assert( windowPointer != NULL && "Window::Window - GLFW returned NULL pointer for windowPointer" );

		glfwMakeContextCurrent( windowPointer );
		glfwSwapInterval( 1 );
	}

	~Window( void ) {
		assert( windowPointer != NULL && "Window::CleanupWindow - windowPointer is NULL" );
		glfwDestroyWindow( windowPointer );
	}

	void MakeActive( ) {
		glfwMakeContextCurrent( windowPointer );
	}

	void CloseWindow( ) {
		assert( windowPointer != NULL && "Window::CloseWindow - windowPointer is NULL" );
		return glfwSetWindowShouldClose( windowPointer, GL_FALSE );
	}

	/*void CleanupWindow( ) {
		assert( windowPointer != NULL && "Window::CleanupWindow - windowPointer is NULL" );
		glfwDestroyWindow( windowPointer );
	}*/

	bool Update( ) {
		assert( windowPointer != NULL && "Window::Update - windowPointer is NULL" );
		if( glfwWindowShouldClose( windowPointer ) ) { return false; }
		glfwSwapBuffers( windowPointer );
		return true;
	}
};

class GameEngine {

private:

public:
	GameEngine( void ) {
		bool glfwInitError = glfwInit( );
		assert( glfwInitError == GL_TRUE && "Framework::StartUp - glfwInit returned GL_FALSE" );

		glfwSetErrorCallback( error_callback );
	}

	// Make this the destructor?
	~GameEngine( void ) {
		glfwTerminate( );
	}

	double GetDeltaTime( ) {
		return glfwGetTime( );
	}

	void Update( ) {
		glfwPollEvents( );
	}

};

#endif
