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

# files
###########
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.inl)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE c_sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)

list (APPEND projectFiles ${headers})
list (APPEND projectFiles ${sources})
list (APPEND projectFiles ${c_sources})

# Mirror directory structure in VS
assign_source_group(${projectFiles})

# Create a .exe
add_executable(SpaceFight ${sources} ${c_sources} ${headers})

# It depends on the .dll made in a previous project
target_link_libraries(SpaceFight GeneralLib)

# Also it depends on GLFW
target_link_libraries(SpaceFight glfw)
include_directories("../glfw-3.3/include/GLFW/")

# And also on opengl
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(SpaceFight ${OPENGL_gl_LIBRARY})
target_link_libraries(SpaceFight ${OPENGL_glu_LIBRARY})

# And glad
include_directories("../include/")

# Grab glm from GeneralLib
include_directories("../GeneralLib/include/")
