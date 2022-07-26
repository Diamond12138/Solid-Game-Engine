#version 330 core

layout(location=0)in vec2 a_position;
layout(location=1)in vec4 a_color;
layout(location=2)in vec2 a_texCoord;

out vec2 v_position;
out vec4 v_color;
out vec2 v_texCoord;

uniform mat4 u_model;

void main()
{
	gl_Position = u_model * vec4(a_position,0.0,1.0);
	v_position = vec2(u_model * vec4(a_position,0.0,1.0));
	v_color = a_color;
	v_texCoord = a_texCoord;
}
