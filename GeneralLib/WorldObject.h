#pragma once

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class C_Model;

/**
* A basic superclass for instances which have a presence somewhere in the game world.
*/
class C_WorldObject
{
public:
	C_WorldObject(glm::vec3 position, glm::quat rotation, C_Model * model);
	C_WorldObject(glm::vec3 position, C_Model * model);

	glm::mat4 getModelMatrix() const;

	void step(float deltaTime);

	C_Model * mp_Model; /** The model representing this objects vertices etc*/

protected:
	glm::vec3 m_Position; /** The world coordinates for the center of the object*/
	glm::quat m_Rotation; /** Quaternion of the current rotation of the object in the game world*/

	glm::vec3 m_Speed;
	glm::vec3 m_AngularVelocity;
};