#include "catch.hpp"
#include "FilePath.h"
#include <string>

TEST_CASE("FilePath works as expected", "[FilePath]")
{
	SECTION("Relative path works")
	{
		std::string xString = R"(\foo\bar\)";
		std::string yString = R"(\foo\bar\foo.txt)";

		C_FilePath x = xString;
		C_FilePath y = yString;

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

		C_FilePath x = xString;
		C_FilePath y = yString;

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

	SECTION("List constructor works")
	{
		C_FilePath x = { "foo", "bar" };
		
		REQUIRE(x.toString() == R"(\foo\bar\)");
		REQUIRE(C_FilePath({ "foo", "bar" }).toString() == x.toString());
	}

	SECTION("toString with & without file works")
	{
		C_FilePath x = R"(\foo\bar\foo.bar)";

		REQUIRE(x.toString(false) == R"(\foo\bar\foo.bar)");
		REQUIRE(x.toString(true) == R"(\foo\bar\)");
	}

	SECTION("Operator+ overload works")
	{
		std::string xString = R"(C:\foo\bar\)";
		std::string yString = R"(foo\bar\foo.txt)";

		C_FilePath x = xString + yString;
		C_FilePath a = xString;
		C_FilePath b = yString;
		C_FilePath y;
		y = a + b;

		REQUIRE(x.toString() == y.toString());
		REQUIRE(x.isRelative() == y.isRelative());
		REQUIRE(x.isFile() == y.isFile());
		REQUIRE(x.isDirectory() == y.isDirectory());
		REQUIRE(x.size() == y.size());
	}

	SECTION("operator-- overloads work")
	{
		C_FilePath x = R"(\foo\bar.txt)";
		C_FilePath xCopy = x;
		C_FilePath y = R"(\foo\)";

		REQUIRE(x-- == xCopy);
		REQUIRE(x != xCopy);
		REQUIRE(x == y);
		REQUIRE(--xCopy == y);
	}
}