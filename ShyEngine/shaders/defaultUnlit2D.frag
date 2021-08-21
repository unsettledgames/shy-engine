#version 130

in vec2 fragUV;
in vec4 fragColor;
in vec2 fragPos;

out vec4 finalFragColor;

uniform sampler2D mainTexture;
uniform float time;

void main()
{ 
	vec4 texColor = vec4(1,0,0,1);
	texColor.xy = fragPos.xy; //texture(mainTexture, fragUV) * fragColor;
	
	// Useless
	vec4 sas2 = texture(mainTexture, fragUV);
	float sas = time;
	
	/*	finalFragColor = vec4(
		fragColor.r * (cos(fragPos.x + time) + 1) / 2,
		fragColor.g * (cos(fragPos.y + time) + 1) / 2,
		fragColor.b, fragColor.a
	) + vec4((cos(time) + 1) / 2, (cos(time + 2) + 1) / 2, (sin(time + 1) + 1) / 2, 0);*/
	
	finalFragColor = texColor;
}