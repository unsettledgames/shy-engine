#version 130

in vec2 vertPos;
in vec4 vertColor;
in vec2 vertUV;

out vec4 fragColor;
out vec2 fragPos;
out vec2 fragUV;

void main()
{
	gl_Position.xy = vertPos;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;

	fragColor = vertColor;
	fragPos = vertPos;
	fragUV = vertUV;
}