#ifndef _GODFRAME_H_
#define _GODFRAME_H_

#include <string>
#include <vector>
#include "OpenGL_Tools.h" // GLEW, GLFW, GLM

#include "GLPrimitive.h"
#include "GLPoint.h"
#include "GLTri.h"

// Function for GLFW error handling. Not recomended for actual use.
static void error_callback( int error, const char* description ) { assert( 0 && description ); }

class GameEngine {

private:
	bool error_glfw; // Did GLFW init properly?
	GLenum error_glew; // Did GLEW init properly?
	unsigned int width, height; // Size of the window
	float color[4]; // Color of the window's background
	GLFWwindow * windowPointer; // Pointer to the window
	std::string name; // Name of the window

public:

	GameEngine( void );

	bool Update( void ); // Polls input, clears window, and other stuff that needs to be done every tick in the background.

	void Window_New( const char* windowName, unsigned int windowWidth, unsigned int windowHeight );
	void Window_Stop( void );
	void Window_Close( void );

	// Getters for window privates
	const char* Window_GetName( void );
	int Window_GetWidth( void );
	int Window_GetHeight( void );

	void Engine_Close( void ); // Shuts down EVERYTHING
	double Engine_GetTime( void );
	void Engine_SetBackgroundColor( float r, float g, float b, float a );

};

#endif
