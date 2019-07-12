#pragma once

#include <unordered_map>

/**
* A template class which just remembers which S_Entity.m_ID's have this particular component.
* 
* Provides methods to access the specific component for any given ID.
* 
* The type of component to manage is simply the type of the C_ComponentManager
*/
template <class T>
class C_ComponentManager
{
public:
	/**
	* Get the actual component for the S_Entity with the given ID
	* 
	* @param uniqueID The ID to get the component for
	* @return The actual component object
	*/
	T& getComponent(unsigned int uniqueID)
	{
		// Using operator[] would default construct the component if it wasn't already there
		return m_Components.at(uniqueID);
	}

	/**
	* Check if the given ID has this component
	*
	* @param uniqueID The ID to check for a component of
	* @return true if the S_Entity.m_ID is registered with this C_ComponentManager
	*/
	bool hasComponent(unsigned int uniqueID)
	{
		return m_Components.count(uniqueID) == 1;
	}

	/**
	* Add this type of component to the given ID
	*
	* @param uniqueID The ID to add the component to
	* @param newComponent The actual new component
	*/
	void addComponent(unsigned int uniqueID, T newComponent)
	{
		m_Components.insert({ uniqueID, newComponent });
	}

	/**
	* Add this type of component to the given ID
	* 
	* The component will be default constructed
	*
	* @param uniqueID The ID to add the component to
	*/
	void addComponent(unsigned int uniqueID)
	{
		// operator[] calls the default constructor if the element doesn't exist yet
		m_Components[uniqueID];
	}

	/**
	* Remove this type of component from the given ID
	*
	* @param uniqueID The ID to remove the component from
	*/
	void removeComponent(unsigned int uniqueID)
	{
		m_Components.erase(uniqueID);
	}

private:
	std::unordered_map< unsigned int, T > m_Components; /** Map from ID to the component object*/
};