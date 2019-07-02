#pragma once

#include <memory>

#include "glm/glm.hpp"

#include "Model.h"

/**
* A basic superclass for instances which have a presence somewhere in the game world.
*/
class WorldObject
{
	glm::vec3 position; /** The world coordinates for the center of the object*/
	glm::mat4 rotation; /** The current rotation of the object in the game world*/
	std::unique_ptr<Model> model; /** The model representing this objects vertices etc*/
};