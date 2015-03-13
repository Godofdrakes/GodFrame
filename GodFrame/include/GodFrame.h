#ifndef _GODFRAME_H_
#define _GODFRAME_H_

#include <string>
#include "OpenGL_Tools.h" // GLEW and GLFW
#include "GLM_Tools.h" // GLM
#include "GLObjects.h"

// Function for GLFW error handling. Not recomended for actual use.
static void error_callback( int error, const char* description ) { assert( 0 && description ); }

struct ShaderProgram {
	GLuint handle;
	GLuint positionAttrib;
	GLuint textureAttrib;
	GLuint vertex;
	GLuint fragment;
};

class GameEngine {

private:
	static bool engineHasStarted;
	static unsigned int width, height; // Size of the window
	static float color[4]; // Color of the window's background
	static GLFWwindow * windowPointer; // Pointer to the window
	static std::string name; // Name of the window
	static glm::mat4 m4_projection;
	static ShaderProgram textured, untextured;

	static void Shader_Load( const char * fileName, GLuint & shaderIndex, GLuint shaderType );
	static void Shader_Link( GLuint & shader_program, GLuint & shader_vertex, GLuint & shader_fragment, bool textured );

	static void Window_New( const char* windowName, unsigned int windowWidth, unsigned int windowHeight );

public:

	GameEngine( const char* windowName, unsigned int windowWidth = 1024, unsigned int windowHeight = 768 );

	static bool Window_Update( void ); // Polls input, clears window, and other stuff that needs to be done every tick in the background.
	static void Window_Stop( void );
	static void Window_Close( void );

	// Getters for window privates
	static const char* Window_GetName( void );
	static int Window_GetWidth( void );
	static int Window_GetHeight( void );

	static void Engine_Close( void ); // Shuts down EVERYTHING
	static double Engine_GetTime( void );
	static void Engine_SetBackgroundColor( float r, float g, float b, float a );

	static GLPrimitive * MakeObject( GL_PRIMITIVE type );

};

#endif
