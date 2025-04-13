# Find source files for tests
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Create the single test executable
add_executable(PhysicsSimulation_tests ${TEST_SOURCES})

# Add source files from the main project that the tests depend on
# Adjust paths if your source directory is different
# Assuming vector implementation is header-only or also in vector.cpp
target_sources(PhysicsSimulation_tests PRIVATE
    ../source/particle.cpp
    ../source/particlegenerator.cpp
    ../source/euler.cpp
    ../source/verlet.cpp
    ../source/gravity.cpp
    ../source/spring.cpp

    # Add the fake graphics implementation FOR THE TEST BUILD ONLY
    fake_graphics.cpp
)

# Add include directories needed by the tests target
# Include the main project's include directory
target_include_directories(PhysicsSimulation_tests PRIVATE
    ../include
    # Include the tests directory itself for test_utils.h
    .
)
# Include Google Test headers (assuming googletest variables are set by parent CMakeLists)
target_include_directories(PhysicsSimulation_tests PRIVATE
    ${googletest_SOURCE_DIR}/googletest/include
    ${googletest_SOURCE_DIR}/googlemock/include
)

# Link test executable against Google Test libraries and any main project library
target_link_libraries(PhysicsSimulation_tests PRIVATE gtest gtest_main gmock)
# If you have a main library target (e.g., PhysicsSimulationLib) defined in the root CMakeLists.txt
# that includes particle.cpp, vector.cpp etc., link against that instead of adding sources directly:
# target_link_libraries(PhysicsSimulation_tests PRIVATE PhysicsSimulationLib gtest gtest_main gmock)

# Discover and add tests from the single executable to CTest
include(GoogleTest)
gtest_discover_tests(PhysicsSimulation_tests)