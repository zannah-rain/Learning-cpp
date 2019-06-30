#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera()
{
	cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::mat4 Camera::view() const
{
	return glm::lookAt(cameraPos, cameraTarget, up);
}

glm::vec3 Camera::cameraForwards() const
{
	return glm::normalize(cameraTarget - cameraPos);
}

glm::vec3 Camera::cameraUp() const
{
	return glm::cross(-cameraForwards(), cameraRight());
}

glm::vec3 Camera::cameraRight() const
{
	return glm::normalize(glm::cross(up, -cameraForwards()));
}

void Camera::move(glm::vec3 translation)
{
	cameraPos += translation;
	cameraTarget += translation;
}