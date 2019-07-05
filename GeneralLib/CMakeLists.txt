# Find opengl
find_package(OpenGL REQUIRED)

if (OPENGL_FOUND)
	message("opengl found")
	message("include dir: ${OPENGL_INCLUDE_DIR}")
	message("link libraries: ${OPENGL_gl_LIBRARY}")
else (OPENGL_FOUND)
	message("opengl not found")
endif()

# Create a dll
add_library (GeneralLib 
	FilePath.h FilePath.cpp 
	FileSystem.h FileSystem.cpp 
	Logger.h Logger.cpp 
	whereami.h whereami.c
	Shader.h Shader.cpp
	stb_image_implementation.cpp
	Texture.h Texture.cpp
	Camera.h Camera.cpp
	Model.h Model.cpp
	wrapFILE.h wrapFILE.cpp
	loadOBJ.h loadOBJ.cpp
	Vertex.h Vertex.cpp
	OGLHandler.h OGLHandler.cpp
	WorldObject.h WorldObject.cpp
	Controllers.h Controllers.cpp)
	
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