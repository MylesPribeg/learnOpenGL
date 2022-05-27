#version 330 core

out vec4 FragColor;

void main()
{
	
	float NDC = gl_FragCoord.z * 2.0 - 1.0;

	float near= 0.1;
	float far = 100.0;
	float linearDepth = (2.0 * near * far) / (far + near - NDC * (far - near));

	
	FragColor = vec4(vec3(linearDepth/far), 1.0);
}
