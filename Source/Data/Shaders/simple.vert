#version 330 core

layout (location = 0) in vec2 in_pos;

uniform vec2 u_pos;
uniform vec3 u_Col;

out vec3 col;

void main()
{
	gl_Position = vec4(in_pos.x + u_pos.x, in_pos.y + u_pos.y, 0, 1);

	col = u_Col;
}