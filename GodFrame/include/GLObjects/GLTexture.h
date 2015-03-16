#ifndef _GLTEXTURE_H_
#define _GLTEXTURE_H_

#include "GLPrimitive.h"
#include <SOIL\SOIL.h>

class GLTexture : public GLPrimitive {

private:
	GLuint texture;
	GLuint uvo; // Texture UV
	float uvData[8];

public:

	GLTexture( GLuint shader, glm::mat4 projection, const char * filePath );
	~GLTexture( void );

	DERIVED_GL_PRIMITIVE

};

#endif
