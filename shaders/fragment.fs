#version 330 core
out vec4 fragColor;

in vec3 ownColor;
in vec2 texCoord;

uniform sampler2D slime;
uniform sampler2D face;

void main()
{
	// vec4 texColor = texture(ownTexture, texCoord);
	// fragColor = texColor * vec4(ownColor, texColor.a);
	// fragColor = texture(ownTexture, texCoord);
	vec2 otherDirection = vec2(1.0 - texCoord.x, texCoord.y);
	fragColor = mix(texture(slime, texCoord), texture(face, otherDirection), 0.2);
}