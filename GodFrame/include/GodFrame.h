#ifndef _GODFRAME_H_
#define _GODFRAME_H_

#include <assert.h>
#include <string>
#include "OpenGL_Tools.h" // GLEW, GLFW, GLM

// Function for GLFW error handling. Not recomended for actual use.
static void error_callback( int error, const char* description ) { assert( 0 && description ); }

class GameEngine {

private:
	GLFWwindow * windowPointer;
	unsigned int width, height;
	std::string name;

public:
	double deltaTime;

	GameEngine( void );

	// Window management
	void NewWindow( const char* windowName, unsigned int windowWidth, unsigned int windowHeight );
	void EndWindow( );
	void CloseWindow( );

	void ShutDown( void ); // Shuts down EVERYTHING

	double GetDeltaTime( );

	bool Update( );

};

#endif
