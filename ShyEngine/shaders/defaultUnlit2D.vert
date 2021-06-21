#version 130

in vec2 vertPos;
in vec4 vertColor;

out vec4 fragColor;

void main()
{
	gl_Position.xy = vertPos;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fragColor = vertColor;
}