#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>


class Shader
{
public:
	unsigned int ID; // program ID

	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string name, float v1, float v2, float v3) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
};

