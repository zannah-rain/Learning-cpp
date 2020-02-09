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

# Create a static library
add_library (GeneralLib ${sources} ${c_sources} ${headers})

# Mirror directory structure in VS
assign_source_group(${projectFiles})
	
# Also it depends on GLFW
target_link_libraries(GeneralLib glfw)
include_directories("../glfw-3.3/include/GLFW/")

# And also on opengl
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(GeneralLib ${OPENGL_gl_LIBRARY})
target_link_libraries(GeneralLib ${OPENGL_glu_LIBRARY})

# And glad
include_directories("../include/")

# Make sure the compiler can find include files for our GeneralLib library
# when other libraries or executables link to GeneralLib
target_include_directories (GeneralLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})