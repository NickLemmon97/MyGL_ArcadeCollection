#version 330 core

layout (location = 0) in vec2 in_pos;

uniform vec2 u_pos;

uniform vec2 u_campos;
uniform vec2 u_ProjectionScale;
uniform vec2 u_ScreenSize;
uniform vec2 u_anchor;

uniform float u_rotation;

void main()
{
	vec2 pos = vec2( 
	u_ScreenSize.x - (u_ScreenSize.x * -u_anchor.x),  
	u_ScreenSize.y - (u_ScreenSize.y * -u_anchor.y));

	pos += u_pos + vec2(
	in_pos.x * cos(u_rotation) - in_pos.y * sin(u_rotation), 
	in_pos.x*sin(u_rotation) + in_pos.y * cos(u_rotation));

	pos += u_pos;
	pos += u_campos;
	pos *= u_ProjectionScale;

	gl_Position = vec4(pos, 0, 1);
}