#pragma once
#ifndef _MESH
#define _MESH

#include "Shader.h"
#include <string>
#include <vector>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture
{
	GLuint id;
	std::string type;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex> &vertices,
		const std::vector<GLuint> &indices,
		const std::vector<Texture> &textures) {
		this->indices = indices;
		this->vertices = vertices;
		this->textures = textures;
		//int c = indices[100000];
		setup();
	}

	void setup();
	void draw(Shader &shader);

//private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
};

#endif // !_MESH
