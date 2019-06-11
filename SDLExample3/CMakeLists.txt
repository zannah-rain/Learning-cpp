# Set the .exe to console mode, and the entry point to main()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")

# Create a .exe
add_executable(SDLExample3 main.cpp)

# It depends on the .dll made in a previous project
target_link_libraries(SDLExample3 GeneralLib)

# Also it depends on SDL!!!!!!
target_link_libraries(SDLExample3 SDL2)