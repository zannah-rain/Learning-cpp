#pragma once

#include <forward_list>

#include "glm/glm.hpp"

#include "ComponentManager.h"
#include "Entity.h"

#include "S_ModelComponent.h"
#include "S_MomentumComponent.h"
#include "S_PositionComponent.h"
#include "S_RotationComponent.h"

class C_EntityComponentSystem
{
public:
	/**
	* Constructor
	* 
	* @param modelShaderLocation Which location in the .glsl shader is used for model coordinate data
	*/
	C_EntityComponentSystem(unsigned int modelShaderLocation);

	/**
	* Create a new (blank) entity
	* 
	* @return The unique id of the entity
	*/
	unsigned int newEntity();

	/**
	* Run all systems on all entities!
	*/
	void step(float deltaTime);

	std::forward_list < S_Entity > m_Entities; /** All current entities */

	C_ComponentManager< S_PositionComponent > m_PositionComponents;
	C_ComponentManager< S_RotationComponent > m_RotationComponents;
	C_ComponentManager< S_ModelComponent > m_ModelComponents;
	C_ComponentManager< S_MomentumComponent > m_MomentumComponents;

private:
	unsigned int m_ModelShaderLocation;
	glm::mat4 m_ModelMatrix;
};