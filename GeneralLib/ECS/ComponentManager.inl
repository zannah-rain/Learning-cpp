#pragma once

#include <tuple> // std::forward_as_tuple
#include <utility> // std::piecewise_construct, std::pair
#include <vector> // std::vector

/**
* A parent class for C_ComponentPool's
* 
* Exists to:
* (1) Provide a mechanism to be able to store vectors of pointers to C_ComponentPools
*/
class C_BaseComponentPool
{

};


/**
* C_ComponentPool contains a vector of components of a given type.
* For each component it stores, it also stores the corresponding Entity ID of the entity which owns it.
* 
* Provides methods to access the specific component for any given ID.
*/
template <class T>
class C_ComponentPool : public C_BaseComponentPool
{
public:
	/**
	* Add this type of component to the given ID
	*
	* @param uniqueID The ID to add the component to
	* @param newComponent The actual new component
	* @return The index of the new component object
	*/
	std::size_t addComponent(int uniqueID, T newComponent)
	{
		m_StoredComponents.push_back({ uniqueID, newComponent });
		return m_StoredComponents.size() - 1;
	}

	/**
	* Add this type of component to the given ID with default constructor
	*
	* @param uniqueID The ID to add the component to
	* @return The index of the new component object
	*/
	std::size_t addComponent(int uniqueID)
	{
		std::pair<int, T>& newComponent = m_StoredComponents.emplace_back();
		newComponent.first = uniqueID;
		return m_StoredComponents.size() - 1;
	}

	/**
	* Construct this type of component in place with the given arguments
	*
	* @param uniqueID The ID to add the component to
	* @param args Arguments to pass to the constructor of T
	* @return The index of the new component object
	*/
	template< class... Args >
	std::size_t addComponent(int&& uniqueID, Args&&... args)
	{
		std::pair<int, T>& newComponent = m_StoredComponents.emplace_back(std::piecewise_construct,
																		  std::forward_as_tuple<int>(uniqueID),
																		  std::forward_as_tuple<Args>(args)...);
		return m_StoredComponents.size() - 1;
	}

	/**
	* Remove this type of component from the given entity.
	*
	* @param entity The entity to remove the component from.
	*/
	void removeComponent(int componentIndex)
	{
		// To avoid O(L) deletion operations, instead the last element replaces the deleted one
		// And then the final element in the vector is deleted instead
		m_StoredComponents[componentIndex] = m_StoredComponents.back();
		m_StoredComponents.erase(m_StoredComponents.size - 1);
	}

	/**
	* Accessor for m_StoredComponents
	* 
	* Accessed BY INDEX, not by entity ID or anything like that
	* 
	* @param componentIndex Which component to access
	* @return A reference to the component object
	*/
	T& getComponent(int componentIndex)
	{
		return std::get< 1 >(m_StoredComponents[componentIndex]);
	}

private:
	std::vector< std::pair<int, T> > m_StoredComponents; /** Each component combined with the Entity ID it refers to*/
};