#version 130

in vec4 fragColor;
in vec2 fragPos;

out vec4 finalFragColor;

uniform float time;

void main()
{
	finalFragColor = vec4(
		fragColor.r * (cos(fragPos.x + time) + 1) / 2,
		fragColor.g * (cos(fragPos.y + time) + 1) / 2,
		fragColor.b, fragColor.a
	) + vec4((cos(time) + 1) / 2, (cos(time + 2) + 1) / 2, (sin(time + 1) + 1) / 2, 0);
}