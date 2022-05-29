#version 420 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

layout (std140, binding = 0) uniform Matrices {
	mat4 projection;
	mat4 view;
};

//uniform mat4 projection;
//uniform mat4 view;

void main()
{
	TexCoords = aPos;
	// the cube moves with the camera
	mat3 skyView3 = mat3(view); //type-casting
	mat4 skyView4 = mat4(skyView3);
	vec4 pos = projection * skyView4 * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}