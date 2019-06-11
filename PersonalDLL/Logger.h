#pragma once
#include <string>

class Logger
{
public:
	Logger(int const initialLevel = 0);
	void log(std::string const message, int const level = 0);
private:
	int printLevel = 0;
};

