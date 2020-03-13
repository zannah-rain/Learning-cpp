#include "ECS/System.h"
#include "ECS/World.h"

#include "OpenGL/SpriteRenderer.h"


class C_SpriteSystem : public I_System
{
public:
	C_SpriteSystem(C_World & world, C_SpriteRenderer* sprite_renderer);
	
	void step(C_World & world, float deltaTime);

private:
	std::size_t m_PositionComponentID = 0;
	std::size_t m_RotationComponentID = 0;
	std::size_t m_SpriteComponentID = 0;

	C_SpriteRenderer* mp_SpriteRenderer;
};