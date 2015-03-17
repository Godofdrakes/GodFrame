#include <fstream>
#include <iostream>

#include "GodFrame.h"

int main( void ) {

	GameEngine Engine( "GodFrame", 512, 512 ); // Inits the Engine

	GLPrimitive * texture = Engine.MakeObject( GLTEXTURE, "engine/image/test.png" );
	glm::vec2 pos = glm::vec2( 0, 0 );
	texture->Scale( 64, 64 );
	texture->Move( pos.x, pos.y );
	float speed = 3.f;

	GLPrimitive * line = Engine.MakeObject( GLLINE );
	line->Scale( 64, 64 );
	line->Move( pos.x, pos.y );

	Engine.LoadFont( "engine/font/InputMono.fnt" );
	Engine.drawFPS = true;

	const double TIME_TICKRATE = ( 1.0 / 30 );
	double time_old = Engine.Engine_GetTime( );
	double time_lag = 0.0;

	double foo = 0.0;
	int bar = 0;

	while( Engine.Window_Update( ) ) {
		double time_now = Engine.Engine_GetTime( );
		double time_passed = time_now - time_old;
		time_old = time_now;
		time_lag += time_passed;

		double mouse_x, mouse_y;
		Engine.Input_MousePos( mouse_x, mouse_y );

		while( time_lag >= TIME_TICKRATE ) {
			// Do thinking stuff here

			if( Engine.Input_KeyboardButton( GLFW_KEY_W ) ) {
				pos.y += speed;
			}
			if( Engine.Input_KeyboardButton( GLFW_KEY_S ) ) {
				pos.y -= speed;
			}
			if( Engine.Input_KeyboardButton( GLFW_KEY_A ) ) {
				pos.x -= speed;
			}
			if( Engine.Input_KeyboardButton( GLFW_KEY_D ) ) {
				pos.x += speed;
			}

			// At the end
			time_lag -= TIME_TICKRATE;
		}

		// Do drawing stuff here

		texture->Move( pos.x, pos.y );
		texture->Render( );

		glm::vec2 lineDirection = glm::vec2( mouse_x, mouse_y ) - pos;
		double lineRotation = atan2( lineDirection.y, lineDirection.x );
		double lineLength = abs( mouse_x - pos.x ) + abs( mouse_y - pos.y );
		line->Scale( 64, 256 );
		line->Rotate( lineRotation );
		line->Move( pos.x, pos.y );
		line->Render( );

		if( Engine.Input_KeyboardButton( GLFW_KEY_ESCAPE ) ) { Engine.Window_Stop( ); }
	}

	delete texture;

	// Cleanup the windows
	Engine.Window_Close( );
	// Cleanup the engine
	Engine.Engine_Close( );

	return 0;
}