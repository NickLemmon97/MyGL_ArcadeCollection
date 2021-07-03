#version 330 core

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec3 in_col;

out vec3 col;

void main()
{
	gl_Position = vec4(in_pos, 0, 1);

	col = vec3(in_col.xy, 1.0f);
};
