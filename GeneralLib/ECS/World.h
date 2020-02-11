#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "ComponentManager.inl"
#include "Entity.h"
#include "System.h"


class C_World
{
public:
	/**
	* Constructor
	* 
	* @param modelShaderLocation Which location in the .glsl shader is used for model coordinate data
	*/
	explicit C_World();

	/**
	* Create a new (blank) entity
	* 
	* @return A reference to the new entity
	*/
	int newEntity();

	/**
	* Ensures we have a unique integer id for every type of component handled by the world
	* 
	* When components are added, accessed etc, this index is used to determine where its component manager is
	* stored in m_ComponentPools
	*/
	// TODO: Check that this is used consistently, I think components themselves declare this now?
	template< class T >
	std::size_t componentTypeID()
	{
		static std::size_t id = registerNewComponentType< T >();
		return id;
	}

	/**
	* Add a given component to a given entity (by entity id)
	* 
	* Ensures both the entity object & the component manager are updated in tandem
	* 
	* @param entityID The id of the entity to register the new component to
	* @param componentManager The specific component manager to register the component with
	* @param newComponent The actual component to connect the entity with
	*/
	template< class T >
	void addComponent(int entityID, T newComponent)
	{
		// Adds the id, component pair to the component manager
		// Adds a reference to the component storage location in the entity
		m_Entities[entityID].addComponent(componentTypeID< T >(), getComponentPool< T >().addComponent(entityID, newComponent));
	}

	// Overload of the above to use the default constructor
	template< class T >
	void addComponent(int entityID)
	{
		// Add a default constructed component of the given type
		m_Entities[entityID].addComponent(componentTypeID< T >(), getComponentPool< T >().addComponent(entityID));
	}

	// Overload of the above to construct the component in place
	template< class T, class... Args >
	void addComponent(int entityID, Args&&... args)
	{
		m_Entities[entityID].addComponent(componentTypeID< T >(), getComponentPool< T >().addComponent(entityID, std::forward< Args >(args)...));
	}

	/**
	* Create a new system object in place
	*/
	template< class T, class... Args >
	void addSystem(Args&&... args)
	{
		std::cout << "C_World:: Registered System " << m_Systems.size() << std::endl;
		I_System * p_BasePointer = new T(std::forward< Args >(args)...);
		m_Systems.push_back(std::unique_ptr< I_System >(p_BasePointer));
	}

	/**
	* Run all systems on all entities!
	*/
	void step(float deltaTime);

	/**
	* Get a reference to a component pool
	*/
	template< class T >
	C_ComponentPool< T >& getComponentPool(std::size_t componentType)
	{
		static C_ComponentPool< T >& this_pool(static_cast<C_ComponentPool< T >&>(*m_ComponentPools[componentType]));
		return this_pool;
	}

	/**
	* Get a reference to a component pool in a slightly friendlier way :)
	*/
	template< class T >
	C_ComponentPool< T >& getComponentPool()
	{
		return getComponentPool< T >(componentTypeID< T >());
	}


	std::vector < C_Entity > m_Entities; /** Central record of all Entities */

private:
	/**
	* Adds a new component type to the component pools
	*
	* @return The index of the new component pool in m_ComponentPools
	*/
	template< class T >
	std::size_t registerNewComponentType()
	{
		std::cout << "C_World:: Registered Component Type " << m_NumComponentTypesRegistered << std::endl;
		m_ComponentPools.push_back(std::make_unique< C_ComponentPool<T> >());
		return m_NumComponentTypesRegistered++;
	}

	std::vector< std::unique_ptr< I_System > > m_Systems;
	std::vector< std::unique_ptr< C_BaseComponentPool > > m_ComponentPools;
	std::size_t m_NumComponentTypesRegistered = 0;
};