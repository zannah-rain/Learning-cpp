#pragma once

class C_System
{
public:
	virtual void step(float deltaTime) = 0;

	virtual ~C_System() {}
};