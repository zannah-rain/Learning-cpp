#pragma once

#include <memory>

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

class Model;

/**
* A basic superclass for instances which have a presence somewhere in the game world.
*/
class WorldObject
{
public:
	WorldObject(glm::vec3 position, glm::quat rotation, Model * model);
	WorldObject(glm::vec3 position, Model * model);

	glm::mat4 getModelMatrix() const;

	Model * mpModel; /** The model representing this objects vertices etc*/

private:
	glm::vec3 mPosition; /** The world coordinates for the center of the object*/
	glm::quat mRotation; /** Quaternion of the current rotation of the object in the game world*/
};