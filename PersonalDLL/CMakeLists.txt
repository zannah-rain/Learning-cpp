# Add precompiler definitions
# Applies this to the current directory & all the ones below
# So there's no need to worry about later projects importing .h files wrong
add_definitions (-D LIBRARY_EXPORTS)

# Create a dll
add_library (PersonalDLL SHARED FilePath.h FilePath.cpp FileSystem.h FileSystem.cpp Logger.h Logger.cpp)

# Make sure the compiler can find include files for our PersonalDLL library
# when other libraries or executables link to PersonalDLL
target_include_directories (PersonalDLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})