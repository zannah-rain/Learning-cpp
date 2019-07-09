#pragma once
#include <string>

/**
 * A class to route all console / other logging output through
 */
class C_Logger
{
public:
	/**
	 * Create a C_Logger with a given initial minimum priority level
	 * @param initialLevel The priority level to log it with. If the Loggers m_PrintLevel is higher, it will not be logged
	 */
	C_Logger(int const initialLevel = 0); /** Basic constructor */

	/**
	 * Log a given message at a given priority level
	 * @param message The message to log
	 * @param level The priority level to log it with. If the Loggers m_PrintLevel is higher, it will not be logged
	 * @return void
	 */
	void log(std::string const message, int const level = 0) const;

private:
	int m_PrintLevel = 0; /** Stores the minimum priority level for a message to have for it to be logged rather than ignored */
};

