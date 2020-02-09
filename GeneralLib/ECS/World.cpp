#include "World.h"


C_World::C_World()
{

}


int C_World::newEntity()
{
	m_Entities.emplace_back(m_NumComponentTypesRegistered);
	return m_Entities.back().id();
}


void C_World::step(float deltaTime)
{
	for (std::unique_ptr< I_System > & i : m_Systems)
	{
		i->step(*this, deltaTime);
	}
}