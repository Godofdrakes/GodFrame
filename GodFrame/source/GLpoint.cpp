#include "../include/GLpoint.h"

void GenBuffers( void );
void DestroyBuffers( void );

void BindBuffers( void );
void BufferVBO( void );
void BufferUVO( void );
void BufferEBO( void );

void LoadTexture( const char* fileName );

void SetSize( float set_width, float set_height );
void SetSize( glm::vec2 position );

void SetPosition( float set_width, float set_height );
void SetPosition( glm::vec2 position );

void SetColor( float red, float green, float blue, float alpha );
void SetColor( glm::vec4 color );

void SetRotaionRad( float radians );
void SetRotaionDeg( float degrees );

void SetMVP( glm::mat4 projection );