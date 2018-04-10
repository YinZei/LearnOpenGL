#pragma once
#ifndef _MODEL
#define _MODEL

#include <map>
#include <string>
#include <vector>
#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <stb_image.h>

class Model
{
public:
	Model(const std::string &path) { loadModel(path); }
	void draw(Shader &shader);
//private:
	std::map<std::string, Texture> loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	void loadModel(const std::string &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	GLuint loadFromFile(std::string name);
};

#endif // !_MODEL
