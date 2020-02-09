#pragma once

#include <vector>

/**
* An entity in an entity component system
* 
* Just a unique ID to be registered / deregistered with different ComponentManagers
*/
struct C_Entity
{
public:
	/**
	* Basic constructor, just makes sure to iterate s_NextID
	*/
	explicit C_Entity(std::size_t numberOfComponentTypes);

	/**
	* Check if this entity has the given component
	* 
	* @param componentType The type of component to check for
	*/
	bool hasComponent(std::size_t componentTypeIndex) const;

	/**
	* Get the index of the given component type
	* 
	* @param componentType The type of component to check for
	*/
	int getComponentIndex(std::size_t componentTypeIndex) const;

	/**
	* Add the component of the given type at the given index to the entities register
	* @param componentTypeIndex The index of the component type for the entities world
	* @param componentVectorIndex The index of the actual component object within the worlds component array
	*/
	bool addComponent(std::size_t componentTypeIndex, std::size_t componentVectorIndex);

	/**
	* Accessor to m_ID
	*/
	int id() const;

private:

	int m_ID; /** The unique ID of this entity*/

	std::vector< std::pair< bool, std::size_t > > m_Components; /** Existence & Locations for this entities components*/

	static unsigned int s_NextID; /** The unique ID of the next entity!*/
};