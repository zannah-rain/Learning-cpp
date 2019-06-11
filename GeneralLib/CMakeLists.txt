# Create a dll
add_library (GeneralLib FilePath.h FilePath.cpp FileSystem.h FileSystem.cpp Logger.h Logger.cpp whereami.h whereami.c)

# Make sure the compiler can find include files for our GeneralLib library
# when other libraries or executables link to GeneralLib
target_include_directories (GeneralLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})