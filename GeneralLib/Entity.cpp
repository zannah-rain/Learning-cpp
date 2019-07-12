#include "Entity.h"

S_Entity::S_Entity()
	: m_ID(S_Entity::s_NextID++)
{

}

unsigned int S_Entity::s_NextID = 0;