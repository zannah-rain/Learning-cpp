#include "C_HealthbarSystem.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include "ECS/ComponentManager.inl"
#include "../Components/S_PositionComponent.h"
#include "../Components/S_ShipStatsComponent.h"

#include "OpenGL/Vertex.h"


C_HealthbarSystem::C_HealthbarSystem(C_World & world, unsigned int healthbarShaderLocation)
	: m_PositionComponentID(world.componentTypeID< S_PositionComponent >())
	, m_ShipStatsComponentID(world.componentTypeID< S_ShipStatsComponent >())
	, m_HealthbarShaderLocation(healthbarShaderLocation)
	, m_VAO(0)
	, m_VBO(0)
{
	// Initialise VAO & VBO
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	// Send static healthbar data to the GPU
	bufferData();
}


void C_HealthbarSystem::bufferData() const
{
	// Placeholder, need to actually generate the vertices from the health probably
	std::vector < float > vertices;

	// VBO STUFF
	// Bind the VBO (The raw vertex data)
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_DYNAMIC_DRAW);

	S_Vertex::configureVAO(m_VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void C_HealthbarSystem::step(C_World & world, float deltaTime)
{
	C_ComponentPool< S_PositionComponent >& positionComponentPool = world.getComponentPool< S_PositionComponent >();
	C_ComponentPool< S_ShipStatsComponent >& shipStatsComponentPool = world.getComponentPool< S_ShipStatsComponent >();
	

	
	for (C_Entity const & i : world.m_Entities)
	{
		if (i.hasComponent(m_PositionComponentID) &&
			i.hasComponent(m_ShipStatsComponentID))
		{
			// TODO
			// Move from model space to world space
			// m_ModelMatrix = glm::translate(glm::mat4(1.0f), positionComponentPool.getComponent(i.getComponentIndex(m_PositionComponentID)).m_Position);

			// Send the modelMatrix to the GPU
			// glUniformMatrix4fv(m_HealthbarShaderLocation, 1, GL_FALSE, glm::value_ptr(m_ModelMatrix));

			// Draw the model
			// model_component_pool.getComponent(i.getComponentIndex(m_ModelComponentID)).m_Model->draw();
		}
	}
}