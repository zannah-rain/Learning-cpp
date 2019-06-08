# Create a .exe
add_executable (PersonalDLLTests main.cpp testFileSystem.cpp)

# It depends on the .dll
target_link_libraries (PersonalDLLTests PersonalDLL)