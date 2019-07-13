#include "S_MomentumComponent.h"


S_MomentumComponent::S_MomentumComponent(glm::vec3 speed, glm::vec3 angularVelocity, float mass)
	: m_Speed(speed)
	, m_AngularVelocity(angularVelocity)
	, m_Mass(mass)
{

}