# Minimum CMake version
cmake_minimum_required (VERSION 2.8.11)

# Define overall project name
project (PersonalStuff)

# Put built objects all in the same folder so they can be run easily
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Build all 3 of my other projects
add_subdirectory (PersonalDLL)
add_subdirectory (PersonalDLLTests)
add_subdirectory (SDLExample3)
add_subdirectory (SDL2-2.0.9)