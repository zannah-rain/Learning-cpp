#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#elif
#    define LIBRARY_API
#endif

#pragma once
#include <string>

class Logger
{
public:
	LIBRARY_API Logger(int const initialLevel = 0);
	LIBRARY_API void log(std::string const message, int const level = 0);
private:
	int printLevel = 0;
};

