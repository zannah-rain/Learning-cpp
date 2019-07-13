#include "catch.hpp"
#include "FileSystem\FileSystem.h"

// For each SECTION, TEST_CASE is run from the start

TEST_CASE("FileSystem works as expected", "[FileSystem]")
{
	C_FileSystem x;
	
	SECTION("members are initialised")
	{
		REQUIRE(x.m_WorkingDirectory.toString().size() > 0);
		REQUIRE(x.getExeDirectory().toString().size() > 0);
	}
}