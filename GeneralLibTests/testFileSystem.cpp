#include "catch.hpp"
#include "FileSystem.h"

// For each SECTION, TEST_CASE is run from the start

TEST_CASE("FileSystem works as expected", "[FileSystem]")
{
	FileSystem x;
	
	SECTION("members are initialised")
	{
		REQUIRE(x.workingDirectory.toString().size() > 0);
		REQUIRE(x.getExeDirectory().toString().size() > 0);
	}
}