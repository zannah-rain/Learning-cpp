#include "C_SpriteSystem.h"

#include "ECS/ComponentManager.inl"
#include "../Components/S_PositionComponent.h"
#include "../Components/S_RotationComponent.h"
#include "../Components/S_SpriteComponent.h"

#include "OpenGL/Texture.h"

#include "ResourceManager.h"


C_SpriteSystem::C_SpriteSystem(C_World & world, C_SpriteRenderer* sprite_renderer)
	: m_PositionComponentID(world.componentTypeID< S_PositionComponent >())
	, m_RotationComponentID(world.componentTypeID< S_RotationComponent >())
	, m_SpriteComponentID(world.componentTypeID< S_SpriteComponent >())
	, mp_SpriteRenderer(sprite_renderer)
{

}


void C_SpriteSystem::step(C_World & world, float deltaTime)
{
	C_ComponentPool< S_PositionComponent >& position_component_pool = world.getComponentPool< S_PositionComponent >();
	C_ComponentPool< S_RotationComponent >& rotation_component_pool = world.getComponentPool< S_RotationComponent >();
	C_ComponentPool< S_SpriteComponent >& sprite_component_pool = world.getComponentPool< S_SpriteComponent >();

	// Activate the 2d shader
	ResourceManager::GetShader("2DShader").use();
	
	// Draw all sprites
	for (C_Entity const & i : world.m_Entities)
	{
		if (i.hasComponent(m_PositionComponentID) &&
			i.hasComponent(m_SpriteComponentID))
		{
			// Draw the sprite
			mp_SpriteRenderer->DrawSprite(
				ResourceManager::GetTexture(sprite_component_pool.getComponent(i.getComponentIndex(m_SpriteComponentID)).m_SpriteName),
				position_component_pool.getComponent(i.getComponentIndex(m_PositionComponentID)).m_Position,
				glm::vec2(100.0f, 100.0f),
				0.0f,
				glm::vec3(1.0f));
		}
	}
}