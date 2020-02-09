#pragma once

class C_World;

class I_System
{
public:
	virtual void step(C_World & world, float deltaTime) = 0;
	
	virtual ~I_System() {};
};