#version 130

in vec4 fragColor;
in vec2 fragPos;
in vec2 fragUV;

out vec4 finalFragColor;

uniform sampler2D mainTexture;
uniform float time;

void main()
{ 
	vec4 texColor = texture(mainTexture, fragUV) * fragColor;
	float sas = time;
	
	/*	finalFragColor = vec4(
		fragColor.r * (cos(fragPos.x + time) + 1) / 2,
		fragColor.g * (cos(fragPos.y + time) + 1) / 2,
		fragColor.b, fragColor.a
	) + vec4((cos(time) + 1) / 2, (cos(time + 2) + 1) / 2, (sin(time + 1) + 1) / 2, 0);*/
	
	finalFragColor = texColor;
}