#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	vec2 smileyTex = vec2(TexCoord.x+0.5, TexCoord.y+0.5);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, smileyTex), 0.2);
}
