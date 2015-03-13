#include <fstream>
#include <iostream>

#include "GodFrame.h"

int main( void ) {

	GameEngine Engine( "GodFrame" ); // Inits the Engine

	GLPrimitive * point = Engine.MakeObject( GLPOINT );
	GLPrimitive * tri = Engine.MakeObject( GLTRI );
	GLPrimitive * line = Engine.MakeObject( GLLINE );
	point->Move( 500, 500 );
	tri->Move( 200, 200 );
	//line->Scale( 1024, 1 );
	//line->Move( 512, 384 );
	//line->Color( 1.f, 0.f, 0.f, 1.f );

	const double TIME_TICKRATE = ( 1.0 / 15 );
	double time_old = Engine.Engine_GetTime( );
	double time_lag = 0.0;

	double foo = 0.0;

	while( Engine.Window_Update( ) ) {
		double time_now = Engine.Engine_GetTime( );
		double time_passed = time_now - time_old;
		time_old = time_now;
		time_lag += time_passed;

		while( time_lag >= TIME_TICKRATE ) {
			// Do thinking stuff here

			++foo;

			// At the end
			time_lag -= TIME_TICKRATE;
		}

		// Do drawing stuff here
		//object->Rotate( foo );
		point->Render( );
		//tri->Rotate( (float)foo );
		tri->Render( );
		//line->Rotate( (float)foo );
		//line->Render( );

		// if( player pressed ESC ) { Engine.Window_Close( ); }
	}

	delete point;
	delete tri;

	// Cleanup the windows
	Engine.Window_Close( );
	// Cleanup the engine
	Engine.Engine_Close( );

	return 0;
}