#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#elif
#    define LIBRARY_API
#endif


#include <string>
#include <iostream>
#include "Logger.h"

LIBRARY_API Logger::Logger(int const initialLevel)
{
	printLevel = initialLevel;
}

void Logger::log(std::string const message, int const level)
{
	if (level >= printLevel)
	{
		std::cout << message << "\n";
	}
}
