#include "Entity.h"


S_Entity::S_Entity()
	: m_ID(S_Entity::s_NextID++)
{

}


S_Entity::operator unsigned int() const
{
	return m_ID;
}


unsigned int S_Entity::s_NextID = 0;