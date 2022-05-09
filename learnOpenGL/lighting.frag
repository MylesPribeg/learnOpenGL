#version 330 core
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emissive;
	float shininess;
};
uniform Material material;

struct Light {
	vec3 position;
	//vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};
uniform Light light;

uniform float timeVar;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

//uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
	//ambient
	vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;


	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(material.diffuse, TexCoords)) * light.diffuse;
	//vec3 diffuse = vec3(0.0);
	//specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	vec3 result = (ambient + diffuse + specular) * attenuation;

	if (vec3(texture(material.specular, TexCoords)) == vec3(0.0))
	{
		result = result + vec3(texture(material.emissive, TexCoords + vec2(0.0, timeVar)));
	}

	FragColor = vec4(result, 1.0);
}