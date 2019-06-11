# Create a .exe
add_executable (GeneralLibTests main.cpp testFileSystem.cpp testFilePath.cpp testLogger.cpp)

# It depends on the .dll
target_link_libraries (GeneralLibTests GeneralLib)