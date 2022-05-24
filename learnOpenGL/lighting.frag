#version 330 core
struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D emissive;
	float shininess;
};
uniform Material material;

struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLight[NR_POINT_LIGHTS];

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutoff;
	float outerCutoff;
	
	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};
uniform SpotLight spotLight;

uniform float timeVar;

uniform sampler2D tex1;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

//uniform vec3 objectColor;
uniform vec3 viewPos;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 viewDir);

void main()
{

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
//	for(int i = 0; i < NR_POINT_LIGHTS; i++)
//	{
//		result += CalcPointLight(pointLight[i], norm, FragPos, viewDir);
//	}

	result += CalcSpotLight(spotLight, norm, viewDir);

	//emissions
	/*
	if (vec3(texture(material.texture_specular1, TexCoords)) == vec3(0.0))
	{
		result = result + vec3(texture(material.emissive, TexCoords + vec2(0.0, timeVar)));
	}
	*/

	//FragColor = vec4(result, 1.0);
	FragColor = texture(tex1, TexCoords);
	//FragColor = vec4(1.0);
}

vec3 CalcDirLight(DirLight light, vec3 norm, vec3 viewDir)
{
	//ambient
	vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords)) * light.ambient;

	//diffuse
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(material.texture_diffuse1, TexCoords)) * light.diffuse;
	
	//specular

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.texture_specular1, TexCoords)) * spec * light.specular;
	

	return ambient + diffuse + specular ;
}

vec3 CalcPointLight(PointLight light, vec3 norm, vec3 fragPos, vec3 viewDir)
{
	//ambient
	vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords)) * light.ambient;

	//diffuse
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(material.texture_diffuse1, TexCoords)) * light.diffuse;

	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.texture_specular1, TexCoords)) * spec * light.specular;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	return (ambient + diffuse + specular) * attenuation ;
}

vec3 CalcSpotLight(SpotLight light, vec3 norm, vec3 viewDir)
{
	//light radius 
	vec3 lightDir = normalize(light.position - FragPos);
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutoff - light.outerCutoff;
	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);

	//ambient
	vec3 ambient = vec3(texture(material.texture_diffuse1, TexCoords)) * light.ambient;

	//diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(texture(material.texture_diffuse1, TexCoords)) * light.diffuse;

	//specular
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.texture_specular1, TexCoords)) * spec * light.specular;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));


	return (ambient + (diffuse + specular) * intensity) * attenuation ;
}