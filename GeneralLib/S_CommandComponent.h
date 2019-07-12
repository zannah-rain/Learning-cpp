#pragma once

#include "glm/glm.hpp"

/**
* Component holding information about the command configuration of an element
* 
* Controls aspects of individual agent behaviour frame to frame
*/
struct S_CommandComponent
{
	// Navigation
	glm::vec3 m_TargetLocation; /** Where we want to navigate to*/
	glm::vec3 m_WithdrawLocation; /** If we decide to run, where go?*/
	bool m_CancelNavigationWhenEngaged; /** Whether we should switch to combat manouvers or keep going*/

	// Combat
	float m_PreferredMinHostileDistance; /** How far away we want to be from the closest hostile*/

};