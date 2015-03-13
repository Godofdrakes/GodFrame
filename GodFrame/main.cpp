#include <fstream>
#include <iostream>

#include "GodFrame.h"

//void PrintXML( const char * filePath ) {
//
//	rapidxml::file<> xmlFile( filePath ); // Default template is char
//	rapidxml::xml_document<> doc;
//	doc.parse<0>( xmlFile.data( ) );
//
//	std::cout << doc.first_node( )->name( ) << std::endl;
//	PrintChildNodes( doc.first_node( ) );
//}

int main( void ) {

	GameEngine Engine( "GodFrame" ); // Inits the Engine

	GLPrimitive * point = Engine.MakeObject( GLPOINT );
	point->Move( 10, 10 );

	GLPrimitive * tri = Engine.MakeObject( GLTRI );
	tri->Move( 200, 200 );

	GLPrimitive * line = Engine.MakeObject( GLLINE );
	line->Scale( 1024, 768 );
	line->Move( 512, 384 );
	line->Color( 1.f, 0.f, 0.f, 1.f );

	GLPrimitive * quad = Engine.MakeObject( GLQUAD );
	quad->Scale( 32, 32 );
	quad->Move( 64, 64 );

	GLPrimitive * texture = Engine.MakeObject( GLTEXTURE, "engine/image/test.png" );
	texture->Scale( 32, 32 );
	texture->Move( 64, 64 );

	Engine.LoadFont( "engine/font/InputMono.fnt" );

	const double TIME_TICKRATE = ( 1.0 / 5 );
	double time_old = Engine.Engine_GetTime( );
	double time_lag = 0.0;

	double foo = 0.0;
	int bar = 0;

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
		line->Rotate( foo );
		line->Render( );

		point->Rotate( foo );
		point->Render( );

		tri->Rotate( foo );
		tri->Render( );

		quad->Rotate( foo );
		quad->Render( );

		texture->Render( );

		Engine.fontManager.DrawString( "Ha:Ha:!!|", 64, 500 ); /*
																Needs font scaling, coloring
															   */

		// if( player pressed ESC ) { Engine.Window_Close( ); }
	}

	delete point;
	delete tri;
	delete line;
	delete quad;
	delete texture;

	// Cleanup the windows
	Engine.Window_Close( );
	// Cleanup the engine
	Engine.Engine_Close( );

	return 0;
}