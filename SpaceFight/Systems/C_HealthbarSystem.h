#include "ECS/System.h"
#include "ECS/World.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

class C_HealthbarSystem : public I_System
{
public:
	C_HealthbarSystem(C_World & world, unsigned int healthbarShaderLocation);
	
	void step(C_World & world, float deltaTime);

private:
	void bufferData() const;

	unsigned int m_VAO;
	unsigned int m_VBO;

	std::size_t m_PositionComponentID = 0;
	std::size_t m_ShipStatsComponentID = 0;

	glm::mat4 m_ModelMatrix;

	unsigned int m_HealthbarShaderLocation;
};