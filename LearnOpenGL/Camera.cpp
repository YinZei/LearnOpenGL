#include "Camera.h"

void Camera::move(float x, float y, float z)
{
	view = glm::lookAt(glm::vec3(x, y, z), glm::vec3(x, y, z - 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * view;
	glm::mat4 rotate(1.0f);
	rotate = glm::rotate(rotate, glm::radians(-yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec4 temp = rotate * glm::vec4(x, y, z, 1.0f);
	position.z += temp.z;
	position.x += temp.x;
}

void Camera::rotate(float hori, float vert)
{
	double temp = angle;
	angle += vert;
	if (angle > 89)
	{
		vert = 89 - temp;
		angle = 89;
	}
	if (angle < -89)
	{
		vert = -89 - temp;
		angle = -89;
	}
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(sin(glm::radians(hori)), 0.0f, -cos(glm::radians(hori))), glm::vec3(0.0f, 1.0f, 0.0f)) * view;
	yaw += hori;
}

const glm::mat4 Camera::getMatrix() const
{
	return glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, sin(glm::radians(angle)), -cos(glm::radians(angle))), glm::vec3(0.0f, 1.0f, 0.0f)) * view;
}

const glm::vec3 & Camera::getPosition() const
{
	return position;
}
