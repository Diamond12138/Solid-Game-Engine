#version 330 core

in vec2 a_position;
in vec4 v_color;
in vec2 v_texCoord;

out vec4 o_color;

uniform bool u_enableTexture;
uniform sampler2D u_sampler;
uniform bool u_enableUniformColor;
uniform vec4 u_color;

vec4 getColor()
{
	vec4 color;
	if(u_enableTexture)
	{
		color = texture(u_sampler,v_texCoord);
	}
	else if(u_enableUniformColor)
	{
		color = u_color;
	}
	else
	{
		color = v_color;
	}
}

void main()
{
	o_color = getColor();
}
