#include "catch.hpp"
#include "FilePath.h"
#include <string>

TEST_CASE("FilePath works as expected", "[FilePath]")
{
	SECTION("Relative path works")
	{
		std::string xString = R"(\foo\bar\)";
		std::string yString = R"(\foo\bar\foo.txt)";

		FilePath x = xString;
		FilePath y = yString;

		REQUIRE(x.toString() == xString);
		REQUIRE(x.isRelative());
		REQUIRE(!x.isFile());
		REQUIRE(x.isDirectory());
		REQUIRE(x.size() == 2);

		REQUIRE(y.toString() == yString);
		REQUIRE(y.isRelative());
		REQUIRE(y.isFile());
		REQUIRE(!y.isDirectory());
		REQUIRE(y.size() == 3);
	}

	SECTION("Absolute path works")
	{
		std::string xString = R"(C:\foo\bar\)";
		std::string yString = R"(Z:\foo\bar\foo.txt)";

		FilePath x = xString;
		FilePath y = yString;

		REQUIRE(x.toString() == xString);
		REQUIRE(!x.isRelative());
		REQUIRE(!x.isFile());
		REQUIRE(x.isDirectory());
		REQUIRE(x.size() == 3);

		REQUIRE(y.toString() == yString);
		REQUIRE(!y.isRelative());
		REQUIRE(y.isFile());
		REQUIRE(!y.isDirectory());
		REQUIRE(y.size() == 4);
	}

	SECTION("Operator overloads work")
	{
		std::string xString = R"(C:\foo\bar\)";
		std::string yString = R"(foo\bar\foo.txt)";

		FilePath x = xString + yString;
		FilePath a = xString;
		FilePath b = yString;
		FilePath y;
		y = a + b;

		REQUIRE(x.toString() == y.toString());
		REQUIRE(x.isRelative() == y.isRelative());
		REQUIRE(x.isFile() == y.isFile());
		REQUIRE(x.isDirectory() == y.isDirectory());
		REQUIRE(x.size() == y.size());
	}
}