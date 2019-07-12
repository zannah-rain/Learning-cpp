#pragma once

#include "glm/gtc/quaternion.hpp"

struct S_RotationComponent
{
	glm::quat m_Rotation = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);
};