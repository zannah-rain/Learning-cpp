# Set the .exe to console mode, and the entry point to main()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE /ENTRY:mainCRTStartup")

# Find opengl
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
	message("opengl found")
	message("include dir: ${OPENGL_INCLUDE_DIR}")
	message("link libraries: ${OPENGL_gl_LIBRARY}")
else (OPENGL_FOUND)
	message("opengl not found")
endif()

# Create a .exe
add_executable(learnopengl main.cpp)

# It depends on the .dll made in a previous project
target_link_libraries(learnopengl GeneralLib)

# Also it depends on GLFW
target_link_libraries(learnopengl glfw)

# And also on opengl
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(learnopengl ${OPENGL_gl_LIBRARY})
target_link_libraries(learnopengl ${OPENGL_glu_LIBRARY})

# And glad
include_directories("include/")
