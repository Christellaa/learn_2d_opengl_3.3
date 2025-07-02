#version 330 core
out vec4 fragColor;

in vec3 ownColor;
in vec2 texCoord;

uniform sampler2D ownTexture;

void main()
{
	// vec4 texColor = texture(ownTexture, texCoord);
	// fragColor = texColor * vec4(ownColor, texColor.a);
	fragColor = texture(ownTexture, texCoord);
}