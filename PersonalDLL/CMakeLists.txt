# Create a dll
add_library (PersonalDLL FilePath.h FilePath.cpp FileSystem.h FileSystem.cpp Logger.h Logger.cpp whereami.h whereami.c)

# Make sure the compiler can find include files for our PersonalDLL library
# when other libraries or executables link to PersonalDLL
target_include_directories (PersonalDLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})