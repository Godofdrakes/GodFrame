#version 150 core

in vec2 v2_position;
in vec2 v2_texcoord;

out vec2 v2_Texcoord;

uniform mat4 m4_mvp;

void main() {

	v2_Texcoord = v2_texcoord;
	gl_Position = m4_mvp * vec4( v2_position, 0.0, 1.0 );

}
