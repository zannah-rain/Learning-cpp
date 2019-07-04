#pragma once

#include "glm/glm.hpp"


class Camera
{
public:
	Camera();

	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); /** No rotation along the z axis yet */
	const glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 cameraPos; /** Where the camera is located*/
	glm::vec3 cameraTarget; /** What location the camera is pointing to*/
	
	glm::mat4 view() const; /** The view matrix for this camera*/

	glm::vec3 cameraForwards() const; /** Axis 1*/
	glm::vec3 cameraRight() const; /** Axis 2*/
	glm::vec3 cameraUp() const; /** Axis 3*/

	void move(glm::vec3 translation); /** Translate the location & target */
};