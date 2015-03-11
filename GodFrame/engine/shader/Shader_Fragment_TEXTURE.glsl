#version 150 core

in vec2 v2_Texcoord;

out vec4 v4_outColor;

uniform sampler2D s2_texID;
uniform vec4 v4_color;

void main() {

	v4_outColor = texture( s2_texID, v2_Texcoord) * v4_color;

}
