#pragma once

struct S_ShipStatsComponent
{
	float m_CurrentHealth;
	float m_MaxHealth;

	float m_CurrentShield;
	float m_MaxShield;

	float m_ForwardThrust; /** How much force can be applied forwards (not for rotating / sideways) */
	float m_ManouveringThrust; /** How much force can be applied to turn / sideways */
	float m_MaxSpeed; /** Can go faster but takes damage */
	float m_MaxSpin; /** Can spin faster but takes damage */
};