#pragma once

#include "glm/glm.hpp"


/**
* Component for objects with a sense of momentum / spin
*/
struct S_MomentumComponent
{
	S_MomentumComponent(glm::vec3 speed, glm::vec3 angularVelocity, float mass);

	glm::vec3 m_Speed;
	glm::vec3 m_AngularVelocity;

	float m_Mass;
};