#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
	glm::vec3 position;
	float angle = 0.0f;
	float yaw = 0.0f;
	glm::mat4 view;
public:
	Camera() : view(1.0f), position(0.0f, 0.0f, 0.0f) {}
	void move(float x, float y, float z);
	void rotate(float hori, float vert);
	const glm::mat4 getMatrix() const;
	const glm::vec3 & getPosition() const;
};

#endif