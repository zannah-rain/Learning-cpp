# Minimum CMake version
cmake_minimum_required (VERSION 2.8.11)

# Define overall project name
project (PersonalStuff)

# Put built objects all in the same folder so they can be run easily
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Build all 3 of my other projects
add_subdirectory (GeneralLib)
add_subdirectory (GeneralLibTests)
add_subdirectory (SDLExample3)
add_subdirectory (SDL2-2.0.9 EXCLUDE_FROM_ALL)

# Remove some project spam from IDEs
set_property (GLOBAL PROPERTY USE_FOLDERS ON)



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

# Building the final .exe should only happen if all tests pass
add_dependencies(SDLExample3 GeneralLibTests_run)





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



# VS specific stuff
# Set the actual program as the startup project (what gets run on F5)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDLExample3)