#include "ECS/System.h"
#include "ECS/World.h"

#include "glad/glad.h"
#include "glm/glm.hpp"

class C_MomentumSystem : public I_System
{
public:
	C_MomentumSystem(C_World & world, unsigned int modelShaderLocation);
	
	void step(C_World & world, float deltaTime);

private:
	std::size_t m_PositionComponentID = 0;
	std::size_t m_RotationComponentID = 0;
	std::size_t m_MomentumComponentID = 0;
	std::size_t m_ModelComponentID = 0;

	glm::mat4 m_ModelMatrix;

	unsigned int m_ModelShaderLocation;
};