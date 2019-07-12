#pragma once

/**
* An entity in an entity component system
* 
* Just a unique ID to be registered / deregistered with different ComponentManagers
*/
struct S_Entity
{
public:
	/*
	* Basic constructor, just makes sure to iterate s_NextID
	*/
	S_Entity();
	
	unsigned int m_ID; /** The unique ID of this entity*/

private:
	static unsigned int s_NextID; /** The unique ID of the next entity!*/
};