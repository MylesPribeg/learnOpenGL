#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
//uniform float mixValue;

void main()
{
	vec2 smileyTex = vec2(TexCoord.x, TexCoord.y);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, smileyTex), 0.2);
}
