#include "BMFont.h"

#include <RapidXML/rapidxml_utils.hpp>
#include <iostream>

void BMFont::PrintAttributes( rapidxml::xml_node<char> * node ) {
	int depth = 0;
	rapidxml::xml_node<char> * temp = node;
	while( temp ) {
		temp = temp->parent( );
		++depth;
	}
	for( rapidxml::xml_attribute<> * attr = node->first_attribute( ); attr; attr = attr->next_attribute( ) ) {
		for( int i = 0; i < depth; ++i ) {
			std::cout << " ";
		}
		std::cout << attr->name( ) << " : " << attr->value( ) << std::endl;
	}
}
void BMFont::PrintChildNodes( rapidxml::xml_node<char> * node ) {
	int depth = 0;
	rapidxml::xml_node<char> * temp = node;
	while( temp ) {
		temp = temp->parent( );
		++depth;
	}
	for( rapidxml::xml_node<> * child = node->first_node( ); child; child = child->next_sibling( ) ) {
		for( int i = 0; i < depth; ++i ) {
			std::cout << " ";
		}
		std::cout << child->name( ) << std::endl;
		PrintAttributes( child );
		//PrintChildNodes( child );
	}
}

rapidxml::xml_node<> * BMFont::FindNode( rapidxml::xml_node<char> * node, const char * name ) {
	for( rapidxml::xml_node<> * child = node->first_node( ); child; child = child->next_sibling( ) ) {
		std::string name_LookFor( name );
		std::string name_Child( child->name( ) );
		if( name_Child == name_LookFor ) { return child; }
	}
	return NULL;
}
rapidxml::xml_attribute<> * BMFont::FindAttrib( rapidxml::xml_node<char> * node, const char * name ) {
	for( rapidxml::xml_attribute<> * attrib = node->first_attribute( ); attrib; attrib = attrib->next_attribute( ) ) {
		std::string name_LookFor( name );
		std::string name_Child( attrib->name( ) );
		if( name_Child == name_LookFor ) { return attrib; }
	}
	return NULL;
}

void BMFont::Scale( float scale_x, float scale_y ) {
	glm::vec3 v3_scale = glm::vec3( scale_x, scale_y, 1.f );
	m4_scale = glm::scale( glm::mat4( ), v3_scale );
}
void BMFont::Move( float move_X, float move_y ) {
	glm::vec3 v3_position = glm::vec3( move_X, move_y, 1.f );
	m4_move = glm::translate( glm::mat4( ), v3_position );
}
void BMFont::Color( float color_r, float color_g, float color_b, float color_a ) {
	v4_color = glm::vec4( color_r, color_g, color_b, color_a );
}

BMFont::BMFont( void ) {
	numPages = 0;
	xmlFile = NULL;
	m4_mvp = m4_projection = m4_move = m4_scale = glm::mat4( 1.f );
	v4_color = glm::vec4( 1.f, 1.f, 1.f, 1.f );
}
BMFont::~BMFont( void ) {
	if( xmlFile ) { delete xmlFile; xmlFile = NULL; }
}

bool BMFont::LoadFont( const char * filePath, GLuint shader, glm::mat4 proj ) {

	shader_Program = shader;
	m4_projection = proj;

	assert( filePath );

	xmlFile = new rapidxml::file<>( filePath );
	doc.parse<0>( xmlFile->data( ) );

	rapidxml::xml_node<> * pages = FindNode( doc.first_node( ), "pages" );
	assert( pages != NULL );
	for( rapidxml::xml_node<> * child = pages->first_node( ); child; child = child->next_sibling( ) ) {
		++numPages;
	}
	assert( numPages > 0 );

	vao = new GLuint[numPages];
	glGenVertexArrays( numPages, vao );

	vbo = new GLuint[numPages];
	glGenBuffers( numPages, vbo );

	ebo = new GLuint[numPages];
	glGenBuffers( numPages, ebo );

	uvo = new GLuint[numPages];
	glGenBuffers( numPages, uvo );

	texture = new GLuint[numPages];
	for( rapidxml::xml_node<> * child = pages->first_node( ); child; child = child->next_sibling( ) ) {

		int num = atoi( child->first_attribute( "id" )->value( ) );

		float vertices[] = {
			0.0, 1.0,
			1.0, 1.0,
			1.0, 0.0,
			0.0, 0.0,
		};

		assert( vbo[num] != 0 );
		glBindBuffer( GL_ARRAY_BUFFER, vbo[num] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

		GLuint elements[] = {
			0, 1, 2,
			0, 2, 3,
		};

		assert( ebo[num] != 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[num] );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( elements ), elements, GL_STATIC_DRAW );

		float uvData[] = {
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0,
			0.0, 1.0,
		};

		assert( uvo[num] != 0 );
		glBindBuffer( GL_ARRAY_BUFFER, uvo[num] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( uvData ), uvData, GL_DYNAMIC_DRAW );

		texture[num] = SOIL_load_OGL_texture(
			child->first_attribute( "file" )->value(),
			SOIL_LOAD_RGBA,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT );
		assert( texture[num] != 0 );
	}

	CheckGLError( "LoadFont" );

	return false;
}
void BMFont::UnloadFont( void ) {
	glDeleteTextures( numPages, texture );
	glDeleteBuffers( numPages, uvo );
	glDeleteBuffers( numPages, ebo );
	glDeleteBuffers( numPages, vbo );
	glDeleteVertexArrays( numPages, vao );
}

void BMFont::DrawString( const char * putWordsHere, float move_x, float move_y ) {
	assert( numPages > 0 && putWordsHere );

	rapidxml::xml_node<> * info = FindNode( doc.first_node( ), "info" );
	assert( info != NULL );

	rapidxml::xml_node<> * common = FindNode( doc.first_node( ), "common" );
	assert( common != NULL );
	float scaleW = atof( common->first_attribute( "scaleW" )->value( ) );
	float scaleH = atof( common->first_attribute( "scaleH" )->value( ) );

	rapidxml::xml_node<> * pages = FindNode( doc.first_node( ), "pages" );
	assert( pages != NULL );

	rapidxml::xml_node<> * chars = FindNode( doc.first_node( ), "chars" );
	assert( chars != NULL );

	int i = 0;
	float offset = 0;
	while( putWordsHere[i] != ""[0] ) {

		unsigned int infLoopCatch = 0;

		rapidxml::xml_node<> * pageNode = pages->first_node( );
		rapidxml::xml_node<> * charNode = chars->first_node( );

		int currentChar = atoi( charNode->first_attribute( "id" )->value( ) );

		while( currentChar != (int)putWordsHere[i] ) {
			charNode = charNode->next_sibling( );
			currentChar = atoi( charNode->first_attribute( "id" )->value( ) );
			assert( charNode != NULL );
			++infLoopCatch;
			assert( infLoopCatch < (unsigned int)atoi( chars->first_attribute( )->value( ) ) );
		}

		infLoopCatch = 0;

		while( atoi( charNode->first_attribute( "page" )->value( ) ) != atoi( pageNode->first_attribute( "id" )->value( ) ) ) {
			pageNode = pageNode->next_sibling( );
			assert( pageNode != NULL );
			++infLoopCatch;
			assert( infLoopCatch < (unsigned int)atoi( chars->first_attribute( )->value( ) ) );
		}

		float x = atof( charNode->first_attribute( "x" )->value( ) );
		float y = atof( charNode->first_attribute( "y" )->value( ) );
		float width = atof( charNode->first_attribute( "width" )->value( ) );
		float height = atof( charNode->first_attribute( "height" )->value( ) );
		float xoffset = atof( charNode->first_attribute( "xoffset" )->value( ) );
		float yoffset = atof( charNode->first_attribute( "yoffset" )->value( ) );
		int page = atoi( charNode->first_attribute( "page" )->value( ) );

		Move( move_x + offset, move_y );
		Scale( width, height );
		offset += width;

		assert( glIsProgram( shader_Program ) == GL_TRUE );

		m4_mvp = m4_projection * m4_move * m4_scale;

		glUseProgram( shader_Program );
		glBindVertexArray( vao[page] );

		glBindBuffer( GL_ARRAY_BUFFER, vbo[page] );
		GLuint positionAttrib = glGetAttribLocation( shader_Program, "v2_position" );
		glEnableVertexAttribArray( positionAttrib );
		glVertexAttribPointer( positionAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 );

		float uvData[] = {
			x / scaleW, y / scaleH,
			( x + width ) / scaleW, y / scaleH,
			( x + width ) / scaleW, ( y + height ) / scaleH,
			x / scaleW, ( y + height ) / scaleH,
		};

		glBindBuffer( GL_ARRAY_BUFFER, uvo[page] );
		glBufferData( GL_ARRAY_BUFFER, sizeof( uvData ), uvData, GL_DYNAMIC_DRAW );

		GLuint textureAttrib = glGetAttribLocation( shader_Program, "v2_texcoord" );
		glEnableVertexAttribArray( textureAttrib );

		glVertexAttribPointer( textureAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 );

		glBindTexture( GL_TEXTURE_2D, texture[page] );
		glActiveTexture( GL_TEXTURE0 );
		glUniform1i( glGetUniformLocation( shader_Program, "texID" ), 0 );

		glUniformMatrix4fv( glGetUniformLocation( shader_Program, "m4_mvp" ), 1, GL_FALSE, glm::value_ptr( m4_mvp ) );
		glUniform4fv( glGetUniformLocation( shader_Program, "v4_color" ), 1, glm::value_ptr( v4_color ) );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo[page] );
		glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		glDisableVertexAttribArray( positionAttrib );
		glDisableVertexAttribArray( textureAttrib );

		CheckGLError( "BMFont::DrawString" );

		++i;
		assert( i < 512 );
	}
}