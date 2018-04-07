#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	GLuint ID;

	Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

	void use();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const glm::mat4 & mat) const;
	void setVec3(const std::string &name, const glm::vec3 &value) const;
	void setPointLight(const std::string &name, const glm::vec3 &position,
		const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float constant, float linear, float quadratic);

	void setDirLight(const std::string &name, const glm::vec3 &direction,
		const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);

	void setFlashLight(const std::string &name, const glm::vec3 &ambient, 
		const glm::vec3 &diffuse, const glm::vec3 &specular, float constant, float linear, float quadratic,
		float cutOff, float outerCutOff);
};

#endif // SHADER_H
