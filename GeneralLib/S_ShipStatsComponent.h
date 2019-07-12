#pragma once

struct S_ShipStatsComponent
{
	float currentHealth;
	float maxHealth;

	float currentShield;
	float maxShield;

	float forwardThrust; /** How much force can be applied forwards (not for rotating / sideways) */
	float manouveringThrust; /** How much force can be applied to turn / sideways */
	float maxSpeed; /** Can go faster but takes damage */
	float maxSpin; /** Can spin faster but takes damage */
};