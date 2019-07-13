# Minimum CMake version
cmake_minimum_required (VERSION 2.8.11)

# utility functions
include(build/utils.cmake)

# Define overall project name
project (PersonalStuff)

# Remove some project spam from IDEs (needs to be set before any target definitions)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)

# Put built objects all in the same folder so they can be run easily
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/build/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/build/lib)

# Build all 3 of my other projects
add_subdirectory (GeneralLib)
add_subdirectory (GeneralLibTests)
add_subdirectory (SDLExample3)
add_subdirectory (SDL2-2.0.9 EXCLUDE_FROM_ALL)
add_subdirectory (glfw-3.3 EXCLUDE_FROM_ALL)
add_subdirectory (learnopengl)
add_subdirectory (SpaceFight)





# UNIT TEST INTEGRATION

# A target for running the test executable
add_custom_target(GeneralLibTests_run
	COMMAND GeneralLibTests
	WORKING_DIRECTORY ${CMAKE_CURRENT_BUILD_DIR}
	COMMENT "running unit tests in ${CMAKE_CURRENT_BUILD_DIR}"
)

# Running the test executable should only happen after the test exe is built & the library is built
add_dependencies(GeneralLibTests_run GeneralLibTests)
add_dependencies(GeneralLibTests_run GeneralLib)

# Building further projects should only happen if unit tests are passing
add_dependencies(SDLExample3 GeneralLibTests_run)
add_dependencies(learnopengl GeneralLibTests_run)
add_dependencies(SpaceFight GeneralLibTests_run)



# Copy the resources folder to build/resources if unit testing is successful
add_custom_target(CopyResources
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/build/resources/
)

# SDLExample3 needs those resources
add_dependencies(SDLExample3 CopyResources)
add_dependencies(learnopengl CopyResources)
add_dependencies(SpaceFight CopyResources)





# Set up Doxygen
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)



# Organise stuff in IDEs even more!
set_target_properties (SDL2 doc_doxygen GeneralLibTests_run glfw CopyResources learnopengl SDLExample3 PROPERTIES
	FOLDER Background
)




# VS specific stuff
# Set the actual program as the startup project (what gets run on F5)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SpaceFight)
