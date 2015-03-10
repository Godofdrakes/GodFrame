#include "include\GodFrame.h"

int main( void ) {

	GameEngine Engine; // Inits the Engine
	Engine.NewWindow( "GodFrame", 1024, 768 );

	while( Engine.Update( ) ) {

	}

	// Cleanup the windows
	Engine.CloseWindow( );
	// Cleanup the engine
	Engine.ShutDown( );

	return 0;
}