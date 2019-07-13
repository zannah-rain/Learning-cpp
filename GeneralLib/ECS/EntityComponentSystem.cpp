#include "EntityComponentSystem.h"

#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "OpenGL/Model.h"


C_EntityComponentSystem::C_EntityComponentSystem(unsigned int modelShaderLocation)
	: m_ModelShaderLocation(modelShaderLocation)
{

}


unsigned int C_EntityComponentSystem::newEntity()
{
	m_Entities.emplace_front();
	return m_Entities.front().m_ID;
}


void C_EntityComponentSystem::step(float deltaTime)
{
	for (S_Entity const & i : m_Entities)
	{
		if (m_PositionComponents.hasComponent(i) &&
			m_ModelComponents.hasComponent(i))
		{
			// Move from model space to world space
			m_ModelMatrix = glm::translate(glm::mat4(1.0f), m_PositionComponents.getComponent(i).m_Position);

			// Apply rotation if it has the rotationComponent
			if (m_RotationComponents.hasComponent(i))
			{
				m_ModelMatrix *= glm::toMat4(m_RotationComponents.getComponent(i).m_Rotation);

				// Apply momentum if we have all the above + MomentumComponent
				if (m_MomentumComponents.hasComponent(i))
				{
					m_PositionComponents.getComponent(i).m_Position += m_MomentumComponents.getComponent(i).m_Speed * deltaTime;
					m_RotationComponents.getComponent(i).m_Rotation *= glm::quat(m_MomentumComponents.getComponent(i).m_AngularVelocity * deltaTime);
				}
			}

			// Send the modelMatrix to the GPU
			glUniformMatrix4fv(m_ModelShaderLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

			// Draw the model
			m_ModelComponents.getComponent(i).m_Model->draw();
		}
	}
}