#version 330 core

in GS_OUT{
	vec2 TexCoords;
	vec3 Normal;
} gs_in;

struct Material{
	sampler2D texture_diffuse1;
};
uniform Material material;

out vec4 FragColor;

void main()
{

	FragColor = vec4(vec3(texture(material.texture_diffuse1, gs_in.TexCoords)), 1.0);
	//FragColor = vec4(1.0);
}