#include "GLObjectManager.h"

#include <assert.h>
#include <fstream>
#include <vector>

#ifdef _DEBUG
#include <iostream> // Only gets used in debug error reporting
#endif

RenderObject::RenderObject( void ) {
	glObject = NULL;
	shader = 0;
}
RenderObject::RenderObject( const RenderObject & other ) {
	glObject = other.glObject;
	shader = other.shader;
	mvp = other.mvp;
}
RenderObject::RenderObject( GLPrimitive * object, GLuint shaderHandle, glm::mat4 set_mvp ) {
	glObject = object;
	shader = shaderHandle;
	mvp = set_mvp;
}
void RenderObject::Render( void ) {
	assert( glObject != NULL && "| RenderObject::Render - invalid glObject |" );
	glObject->SetMVP( mvp );
	glObject->Render( shader );
}
void RenderObject::Rotate( float radians ) {
	assert( glObject != NULL && "| RenderObject::Rotate - invalid glObject |" );
	glObject->Rotate( radians );
}
void RenderObject::Scale( float scale_x, float scale_y ) {
	assert( glObject != NULL && "| RenderObject::Scale - invalid glObject |" );
	glObject->Scale( scale_x, scale_y );
}
void RenderObject::Move( float move_X, float move_y ) {
	assert( glObject != NULL && "| RenderObject::Move - invalid glObject |" );
	glObject->Move( move_X, move_y );
}
void RenderObject::Color( float color_r, float color_g, float color_b, float color_a ) {
	assert( glObject != NULL && "| RenderObject::Color - invalid glObject |" );
	glObject->Color( color_r, color_g, color_b, color_a );
}

void ShaderProgram::LoadShader( const char * fileName, GLuint & shaderIndex, GLuint shaderType ) {

	std::ifstream ifs( fileName, std::ios::in | std::ios::binary | std::ios::ate );

	std::ifstream::pos_type fileSize = ifs.tellg( );
	ifs.seekg( 0, std::ios::beg );

	std::vector<char> bytes( fileSize );
	ifs.read( &bytes[0], fileSize );

	std::string sourceCode( bytes.begin( ), bytes.end( ) );

	const GLchar* sourceChars = sourceCode.c_str( );

	shaderIndex = glCreateShader( shaderType ); // What kind of shader is it?
	glShaderSource( shaderIndex, 1, &sourceChars, NULL ); // Load the code for the shader
	glCompileShader( shaderIndex ); // Build the shader from that code

	// Error checking
	GLint isCompiled = 0;
	glGetShaderiv( shaderIndex, GL_COMPILE_STATUS, &isCompiled );

	if( isCompiled != GL_TRUE ) {
#ifdef _DEBUG
		char buffer[512];
		glGetShaderInfoLog( shaderIndex, 512, NULL, buffer );
		std::cout << buffer << std::endl;
		assert( buffer );
#else
		assert( "| LoadShader - Could not compile shader |" );
#endif
	}
}
void ShaderProgram::LinkShader( GLuint shader_program, GLuint shader_vertex, GLuint shader_fragment, bool textured ) {
	shader_program = glCreateProgram( ); // Create the program
	glAttachShader( shader_program, shader_vertex ); // Load the shaders to it.
	glAttachShader( shader_program, shader_fragment );

	// A fragment shader can have multiple buffers so we need to tell it which output is written where.
	glBindFragDataLocation( shader_program, 0, "v4_outColor" );

	//glTransformFeedbackVaryings( glObject.shader_Program, 1, glObject.feedBack, GL_INTERLEAVED_ATTRIBS );

	// Now we have to link the program.
	glLinkProgram( shader_program );

	GLint isLinked = 0;
	glGetProgramiv( shader_program, GL_LINK_STATUS, &isLinked );
	assert( isLinked = GL_TRUE && "| LoadShaderProgramNOTEXTURE - Could not link shader program |" );

	// To actually use the sahders we have to say we are using the program.
	glUseProgram( shader_program );
	// Only one program can be active at a time.

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	GLuint shaderDataAttrib_Position = glGetAttribLocation( shader_program, "v2_position" );
	glEnableVertexAttribArray( shaderDataAttrib_Position );
	glVertexAttribPointer( shaderDataAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0 );

	if( textured ) {
		GLuint shaderDataAttrib_Position = glGetAttribLocation( shader_program, "v2_texcoord" );
		glEnableVertexAttribArray( shaderDataAttrib_Position );
		glVertexAttribPointer( shaderDataAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	}
}
ShaderProgram::ShaderProgram( void ) { }
ShaderProgram::ShaderProgram( const char * filePath_vertexShader, const char * filePath_fragmentShader, bool useTextures ) {
	LoadShader( filePath_vertexShader, shader_Vertex, GL_VERTEX_SHADER );
	LoadShader( filePath_fragmentShader, shader_Fragment, GL_FRAGMENT_SHADER );
	LinkShader( shader_Program, shader_Vertex, shader_Fragment, useTextures );
}
ShaderProgram::~ShaderProgram( void ) {
	glDetachShader( shader_Program, shader_Vertex );
	glDeleteShader( shader_Vertex );
	glDetachShader( shader_Program, shader_Fragment );
	glDeleteShader( shader_Fragment );
	glDeleteProgram( shader_Program );
}
ShaderProgram & ShaderProgram::operator = ( ShaderProgram & other ) {
	shader_Fragment = other.shader_Fragment;
	shader_Vertex = other.shader_Vertex;
	shader_Program = other.shader_Program
}

RenderObjectManager::RenderObjectManager( void ) { }
RenderObjectManager::RenderObjectManager( glm::mat4 set_projection ) {
	ShaderProgram_TEXTURED = ShaderProgram( "engine/shader/Shader_Vertex_TEXTURE.glsl", "engine/shader/Shader_Fragment_TEXTURE.glsl", true );
	shaderProgram_UNTEXTURED = ShaderProgram( "engine/shader/Shader_Vertex_NOTEXTURE.glsl", "engine/shader/Shader_Fragment_NOTEXTURE.glsl", false );
	projection = set_projection;
}
void RenderObjectManager::SetProjection( glm::mat4 set_projection ) {
	projection = set_projection;
}
RenderObjectManager & RenderObjectManager::operator = ( RenderObjectManager & other ) {
	projection = other.projection;
	ShaderProgram_TEXTURED = other.ShaderProgram_TEXTURED;
	shaderProgram_UNTEXTURED = other.shaderProgram_UNTEXTURED;
}
RenderObjectManager & RenderObjectManager::MakeObject( GL_PRIMITIVE type ) {
	switch( type ) {
	case GLTRI:
		return RenderObject( new GLTri( ), shaderProgram_UNTEXTURED, projection );
		break;

	default:
		assert( "| RenderObjectManager::MakeObject - Invalid type |" );
		break;
	}
}
