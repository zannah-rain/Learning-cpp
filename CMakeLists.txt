# Minimum CMake version
cmake_minimum_required (VERSION 2.8.11)

# Define overall project name
project (PersonalStuff)

# Build all 3 of my other projects
add_subdirectory (PersonalDLL)
add_subdirectory (PersonalDLLTests)
add_subdirectory (SDLExample3)
add_subdirectory (SDL2-2.0.9)