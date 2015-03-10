#include "include\GodFrame.h"

int main( void ) {

	GameEngine Engine; // Inits the Engine
	Window WindowA = Window( "WindowA", 1024, 768 ); // Creates a window.
	Window WindowB = Window( "WindowB", 1024, 768 ); // Creates another, different, window.

	while( WindowA.Update( ) || WindowB.Update() ) {
		Engine.Update( );

		if( WindowA.ShouldClose( ) ) {
			// Do WindowA stuff.
		}

		if( WindowB.ShouldClose( ) ) {
			// Do WindowB stuff.
		}

	}

	// Cleanup the windows
	WindowA.CloseWindow( );
	WindowB.CloseWindow( );
	// Cleanup the engine
	Engine.ShutDown( );

	return 0;
}