#include "catch.hpp"
#include "Logger.h"

TEST_CASE("Logger works as expected", "[FileSystem]")
{
	C_Logger x;

	x.log("test");
}