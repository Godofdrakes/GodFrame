#ifndef _INPUT_KEYMOUSE_H_
#define _INPUT_KEYMOUSE_H_

/* References
	http://www.glfw.org/docs/latest/group__input.html

*/

/* NOTES;
	Abstract these classes?
		Would allow for better cross platform use.
		Would allow for use of other input libraries.

*/

#include "../OpenGL_Tools.h"

class Input_Mouse {

protected:
	double last_mouse_x, last_mouse_y;

public:
	void Init( void );
	void DeInit( void );

	void GetMousePos( GLFWwindow * window, double & mouse_x, double & mouse_y ); // Changes the referenced variables to the mouse cursor's current X/Y position in the window
	bool GetMouseButton( GLFWwindow * window, int mouse_button );

	//void ShowMouse( GLFWwindow * window, bool show ); // HIdes/Shows the mouse cursor.

};

class Input_Keyboard {

protected:

public:
	void Init( void );
	void DeInit( void );

	bool GetKeyboardButton( GLFWwindow * window, int keyboard_button );

};

#endif
