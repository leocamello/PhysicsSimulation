cmake_minimum_required(VERSION 3.11)

project(PhysicsSimulation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Find Required Libraries ---
# Find OpenGL
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found")
endif()

# Check if GLU was found by FindOpenGL
if(NOT TARGET OpenGL::GLU)
    message(FATAL_ERROR "OpenGLU (GLU) not found by FindOpenGL. Try installing libglu1-mesa-dev.")
endif()

# Find GLUT
# Note: Finding GLUT with CMake can be tricky. You might need a FindGLUT.cmake module
# or adjust based on your system's installation (e.g., freeglut).
# This is a basic attempt; you might need to install freeglut-dev (sudo apt install freeglut3-dev)
find_package(GLUT REQUIRED)
if(NOT GLUT_FOUND)
    message(FATAL_ERROR "GLUT not found. Try installing freeglut3-dev.")
endif()

# --- Project Sources ---
# Add include directory
include_directories(include)

# Gather source files
file(GLOB_RECURSE SOURCES "source/*.cpp")

# --- Executable Target ---
add_executable(PhysicsSimulation ${SOURCES})

# --- Link Libraries ---
target_link_libraries(PhysicsSimulation PRIVATE
    OpenGL::GL
    OpenGL::GLU 
    GLUT::GLUT
)

# --- Optional: Doxygen ---
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/docs) # Output to build dir/docs
    set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR})      # Root source dir
    set(DOXYGEN_CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile) # Use Doxyfile from source

    # Add a custom target to run Doxygen
    # Note: This uses the Doxyfile from the source 'docs' dir, but you could also
    # generate one from a Doxyfile.in template if needed.
    add_custom_target(doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs # Run doxygen from the docs dir
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
    message(STATUS "Doxygen found - Added 'doc' target.")
else()
    message(WARNING "Doxygen not found. Documentation generation disabled.")
endif()

# --- Google Test Setup ---
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.16.0 # Or specify a different tag/commit
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add the tests subdirectory
add_subdirectory(tests)