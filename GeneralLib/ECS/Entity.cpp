#include "Entity.h"


C_Entity::C_Entity(std::size_t numberOfComponentTypes)
	: m_ID(C_Entity::s_NextID++)
	, m_Components(numberOfComponentTypes, std::pair< bool, std::size_t >(false, 0))
{

}


bool C_Entity::hasComponent(std::size_t componentTypeIndex) const
{
	return m_Components[componentTypeIndex].first;
}


int C_Entity::getComponentIndex(std::size_t componentTypeIndex) const
{
	return m_Components[componentTypeIndex].second;
}


bool C_Entity::addComponent(std::size_t componentTypeIndex, std::size_t componentVectorIndex)
{
	m_Components[componentTypeIndex].first = true;
	m_Components[componentTypeIndex].second = componentVectorIndex;
	return true;
}


int C_Entity::id() const
{
	return m_ID;
}


unsigned int C_Entity::s_NextID = 0;