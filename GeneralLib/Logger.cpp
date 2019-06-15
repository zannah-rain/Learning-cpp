#include <string>
#include <iostream>
#include "Logger.h"

Logger::Logger(int const initialLevel)
{
	printLevel = initialLevel;
}

void Logger::log(std::string const message, int const level) const
{
	if (level >= printLevel)
	{
		std::cout << message << "\n";
	}
}
