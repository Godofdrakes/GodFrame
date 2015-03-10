#include "include\GodFrame.h"

int main( void ) {

	GameEngine Engine;
	Window GameWindow = Window( "GodFrame", 1024, 768 );
	
	while( GameWindow.Update( ) ) {
		Engine.Update( );
		
	}

	return 0;
}