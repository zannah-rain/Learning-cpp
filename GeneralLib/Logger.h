#pragma once
#include <string>

/**
 * A class to route all console / other logging output through
 */
class Logger
{
public:
	/**
	 * Create a Logger with a given initial minimum priority level
	 * @param initialLevel The priority level to log it with. If the Loggers printLevel is higher, it will not be logged
	 */
	Logger(int const initialLevel = 0); /** Basic constructor */

	/**
	 * Log a given message at a given priority level
	 * @param message The message to log
	 * @param level The priority level to log it with. If the Loggers printLevel is higher, it will not be logged
	 * @return void
	 */
	void log(std::string const message, int const level = 0);
private:
	int printLevel = 0; /** Stores the minimum priority level for a message to have for it to be logged rather than ignored */
};

