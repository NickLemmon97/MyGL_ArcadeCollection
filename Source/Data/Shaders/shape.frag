#version 330 core

uniform vec3 u_Col;

out vec4 frag_col;

void main()
{
	frag_col = vec4(u_Col, 1.0f);
}