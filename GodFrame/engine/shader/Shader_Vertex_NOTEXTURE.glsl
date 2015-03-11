#version 150 core

in vec2 v2_position;

uniform mat4 m4_mvp;

void main() {

	gl_Position = m4_mvp * vec4( v2_position, 0.0, 1.0 );

}
