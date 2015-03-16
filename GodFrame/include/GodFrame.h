#ifndef _GODFRAME_H_
#define _GODFRAME_H_

/* TODO/IDEAS:

	DrawFunction that takes in a GLPrimitive?
		Removes the need to store shaders/projection/mvp itself.

*/

// C++ standard
#include <sstream>
#include <string>

// Base dependencies
#include "OpenGL_Tools.h" // GLEW and GLFW
#include "GLM_Tools.h" // GLM

// Rendering
#include "GLObjects.h"
#include "BMFont.h"

// Input
#include "Input\Input_KeyMouse.h"

// Function for GLFW error handling. Not recomended for actual use.
static void error_callback( int error, const char* description ) { assert( 0 && error && description ); }

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
	static Input_Mouse mouseInput;
	static Input_Keyboard keyboardInput;

	static void Shader_Load( const char * fileName, GLuint & shaderIndex, GLuint shaderType );
	static void Shader_Link( GLuint & shader_program, GLuint & shader_vertex, GLuint & shader_fragment, bool textured );

	static void Window_New( const char* windowName, unsigned int windowWidth, unsigned int windowHeight );

	static void ShowFPS( void );
	static double delta_old, delta_new; // For tracking FPS

public:
	static bool drawFPS;
	static BMFont fontManager;

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

	static void Input_MousePos( double & mouse_x, double & mouse_y );
	static bool Input_MouseButton( int button );
	static bool Input_KeyboardButton( int button );

	static void LoadFont( const char * fontFilePath );

	static GLPrimitive * MakeObject( GL_PRIMITIVE type, const char * optional_textureFilePath = NULL );

};

#endif
