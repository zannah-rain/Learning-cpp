#include <iostream>

#include "Logger.h"


C_Logger::C_Logger(int const initialLevel)
{
	m_PrintLevel = initialLevel;
}


void C_Logger::log(std::string const message, int const level) const
{
	if (level >= m_PrintLevel)
	{
		std::cout << message << "\n";
	}
}
