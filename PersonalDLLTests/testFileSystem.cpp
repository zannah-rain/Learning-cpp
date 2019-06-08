#include "catch.hpp"
#include "FileSystem.h"

// For each SECTION, TEST_CASE is run from the start

TEST_CASE("FileSystem works as expected", "[FileSystem]")
{
	FileSystem x;
	
	SECTION("members are initialised")
	{
		REQUIRE(x.wd.size() > 0);
		REQUIRE(x.exePath.size() > 0);
	}

	SECTION("filePath works as expected")
	{
		REQUIRE(x.filePath({ "X:", "foo", "bar" }) == "X:\foo\bar");
	}
}