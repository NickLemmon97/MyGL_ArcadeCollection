#version 330 core

layout (location = 0) in vec2 in_pos;

uniform vec2 u_pos;

uniform vec2 u_campos;
uniform vec2 u_ProjectionScale;

out vec3 col;

void main()
{
	vec2 pos = in_pos;
	pos += u_pos;
	pos += u_campos;
	pos *= u_ProjectionScale;

	gl_Position = vec4(pos, 0, 1);
}