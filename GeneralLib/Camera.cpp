#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

C_Camera::C_Camera() :
	m_CameraPos(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_CameraTarget(glm::vec3(0.0f, 0.0f, -1.0f))
{

}

glm::mat4 C_Camera::view() const
{
	return glm::lookAt(m_CameraPos, m_CameraTarget, m_Up);
}

glm::vec3 C_Camera::cameraForwards() const
{
	return glm::normalize(m_CameraTarget - m_CameraPos);
}

glm::vec3 C_Camera::cameraUp() const
{
	return glm::cross(-cameraForwards(), cameraRight());
}

glm::vec3 C_Camera::cameraRight() const
{
	return glm::normalize(glm::cross(m_Up, -cameraForwards()));
}

void C_Camera::move(glm::vec3 translation)
{
	m_CameraPos += translation;
	m_CameraTarget += translation;
}