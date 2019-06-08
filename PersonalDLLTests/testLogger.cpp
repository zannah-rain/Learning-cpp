#include "catch.hpp"
#include "Logger.h"

TEST_CASE("Logger works as expected", "[FileSystem]")
{
	Logger x;

	x.log("test");
}