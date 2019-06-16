# Create a .exe
add_executable (GeneralLibTests main.cpp catch.hpp testFileSystem.cpp testFilePath.cpp testLogger.cpp)

# It depends on the library it's testing
target_link_libraries (GeneralLibTests GeneralLib)