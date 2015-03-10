#ifndef _GODFRAME_H_
#define _GODFRAME_H_

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>
#include <GLM\gtc\type_ptr.hpp>
#include <RapidXML\rapidxml.hpp>

/*

function ErrorCallback( int error, const char* description )
	assert( 0 && description )

class GameEngine
	glfwWindowPointer windowPointer

	// Make this the constructor?
	function StartUp( string windowName, unsigned int width, unsigned int height )
		assert( windowName && "Framework::StartUp - Invalid windowName" )
		assert( width > 0 && "Framework::StartUp - width <= 0" )
		assert( height > 0 && "Framework::StartUp - hieght <=0" )

		windowPointer = glfwCreateWindow( width, height, windowName, NULL, NULL )
		assert( windowPointer != NULL && "Framework::StartUp - GLFW returned NULL pointer for windowPointer" )

		glfwSwapInterval(1);
		glfwMakeContextCurrent( windowPointer )

	function WindowShouldClose()
		assert( windowPointer != NULL && "Framework::WindowShouldClose - windowPointer is NULL" )
		return glfwWindowShouldClose( windowPointer )

	function CloseWindow()
		assert( windowPointer != NULL && "Framework::CloseWindow - windowPointer is NULL" )
		return glfwSetWindowShouldClose( windowPointer, GL_FALSE )

	// Make this the destructor?
	function Shutdown( void )
		assert( windowPointer != NULL && "Framework::Shutdown - windowPointer is NULL" )
		glfwDestroyWindow( windowPointer )

	function GetDeltaTime()
		return glfwGetTime()

	function Update()
		assert( windowPointer != NULL && "Framework::Update - windowPointer is NULL" )
		glfwSwapBuffers( windowPointer )
		glfwPollEvents()

int main( void ) {

	GameEngine Engine = GameEngine( "WindowNameHere", 1024, 768 );

	while( !Engine.WindowShouldClose() ) {
		var deltaTime = Engine.GetDeltaTime()
		// Do stuff

		Engine.Update()
	}

	// Engine Destructor gets called(?), performing cleanup.

	return 0;
}
*/

#endif
