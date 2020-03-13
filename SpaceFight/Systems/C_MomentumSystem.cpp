#include "C_MomentumSystem.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "OpenGL/Model.h"

#include "ECS/ComponentManager.inl"
#include "../Components/S_PositionComponent.h"
#include "../Components/S_RotationComponent.h"
#include "../Components/S_MomentumComponent.h"
#include "../Components/S_ModelComponent.h"


C_MomentumSystem::C_MomentumSystem(C_World & world, unsigned int modelShaderLocation)
	: m_PositionComponentID(world.componentTypeID< S_PositionComponent >())
	, m_RotationComponentID(world.componentTypeID< S_RotationComponent >())
	, m_MomentumComponentID(world.componentTypeID< S_MomentumComponent >())
	, m_ModelComponentID(world.componentTypeID< S_ModelComponent >())
	, m_ModelShaderLocation(modelShaderLocation)
{

}


void C_MomentumSystem::step(C_World & world, float deltaTime)
{
	C_ComponentPool< S_PositionComponent >& position_component_pool = world.getComponentPool< S_PositionComponent >();
	C_ComponentPool< S_RotationComponent >& rotation_component_pool = world.getComponentPool< S_RotationComponent >();
	C_ComponentPool< S_MomentumComponent >& momentum_component_pool = world.getComponentPool< S_MomentumComponent >();
	C_ComponentPool< S_ModelComponent >& model_component_pool = world.getComponentPool< S_ModelComponent >();
	for (C_Entity const & i : world.m_Entities)
	{
		if (i.hasComponent(m_PositionComponentID) &&
			i.hasComponent(m_ModelComponentID))
		{
			// Move from model space to world space
			// m_ModelMatrix = glm::translate(glm::mat4(1.0f), position_component_pool.getComponent(i.getComponentIndex(m_PositionComponentID)).m_Position);

			// Apply rotation if it has the rotationComponent
			if (i.hasComponent(m_RotationComponentID))
			{
				m_ModelMatrix *= glm::toMat4(rotation_component_pool.getComponent(i.getComponentIndex(m_RotationComponentID)).m_Rotation);

				// Apply momentum if we have all the above + MomentumComponent
				if (i.hasComponent(m_MomentumComponentID))
				{
					// position_component_pool.getComponent(i.getComponentIndex(m_PositionComponentID)).m_Position += momentum_component_pool.getComponent(i.getComponentIndex(m_MomentumComponentID)).m_Speed * deltaTime;
					rotation_component_pool.getComponent(i.getComponentIndex(m_RotationComponentID)).m_Rotation *= glm::quat(momentum_component_pool.getComponent(i.getComponentIndex(m_MomentumComponentID)).m_AngularVelocity * deltaTime);
				}
			}

			// Send the modelMatrix to the GPU
			glUniformMatrix4fv(m_ModelShaderLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

			// Draw the model
			model_component_pool.getComponent(i.getComponentIndex(m_ModelComponentID)).m_Model->draw();
		}
	}
}