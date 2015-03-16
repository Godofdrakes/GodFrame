#ifndef _BMFONT_H_
#define _BMFONT_H_

#include <RapidXML/rapidxml.hpp> // XML reading
#include <RapidXML/rapidxml_utils.hpp> // Easier XML reading
#include "OpenGL_Tools.h" // OpenGL Rendering
#include <GLM_Tools.h> // Math
#include <SOIL\SOIL.h> // Image loading

class BMFont {

private:
	int numPages;
	float fontScale;

	glm::vec4 v4_color;
	glm::mat4 m4_scale, m4_move, m4_mvp, m4_projection;

	GLuint shader_Program;
	GLuint * vao, * vbo, * ebo, * uvo, * texture;

	rapidxml::file<> * xmlFile;
	rapidxml::xml_document<> doc;

	void PrintAttributes( rapidxml::xml_node<char> * node );
	void PrintChildNodes( rapidxml::xml_node<char> * node );

	rapidxml::xml_node<> * FindNode( rapidxml::xml_node<char> * node, const char * name );
	rapidxml::xml_attribute<> * FindAttrib( rapidxml::xml_node<char> * node, const char * name );

	void Scale( float scale_x, float scale_y );
	void Move( float move_X, float move_y );
	void Color( float color_r, float color_g, float color_b, float color_a );

public:
	BMFont( void );
	~BMFont( void );

	bool LoadFont( const char * filePath, GLuint shader, glm::mat4 proj );
	void UnloadFont( void ); // Unfinished

	void DrawString( const char * putWordsHere, float move_x, float move_y );
	void FontScale( float pixHeight );

};

#endif
