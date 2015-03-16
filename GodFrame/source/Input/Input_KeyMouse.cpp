#include "Input/Input_KeyMouse.h"

void Input_Mouse::Init( void ) {
	last_mouse_x = 0.0;
	last_mouse_y = 0.0;
}
void Input_Mouse::DeInit( void ) {
	// No DeInit necessary
}
void Input_Mouse::GetMousePos( GLFWwindow * window, double & mouse_x, double & mouse_y ) {
	glfwGetCursorPos( window, &last_mouse_x, &last_mouse_y );
	mouse_x = last_mouse_x;
	mouse_y = last_mouse_y;
}
bool Input_Mouse::GetMouseButton( GLFWwindow * window, int mouse_button ) {
	return glfwGetMouseButton( window, mouse_button ) == GLFW_PRESS;
}

void Input_Keyboard::Init( void ) {
	// No Init necessary
}
void Input_Keyboard::DeInit( void ) {
	// No DeInit necessary
}
bool Input_Keyboard::GetKeyboardButton( GLFWwindow * window, int keyboard_button ) {
	return glfwGetKey( window, keyboard_button ) == GLFW_PRESS;
}