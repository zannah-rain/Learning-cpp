#pragma once

#include "glm/glm.hpp"


class C_Camera
{
public:
	C_Camera();

	glm::mat4 view() const; /** The view matrix for this camera*/

	glm::vec3 cameraForwards() const; /** Axis 1*/
	glm::vec3 cameraRight() const; /** Axis 2*/
	glm::vec3 cameraUp() const; /** Axis 3*/

	/**
	* Translate the camera from its current position
	*
	* @param translation The amount to move the camera by in each dimension
	*/
	void move(glm::vec3 translation);



	const glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f); /** No rotation along the z axis yet */
	const glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 m_CameraPos; /** Where the camera is located*/
	glm::vec3 m_CameraTarget; /** What location the camera is pointing to*/
};