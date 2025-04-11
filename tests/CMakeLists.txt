# Find source files for tests
file(GLOB_RECURSE TEST_SOURCES "*.cpp")

# Create the test executable FIRST
add_executable(PhysicsSimulation_tests ${TEST_SOURCES})

# NOW add include directories needed by the tests target
# Include the main project's include directory
target_include_directories(PhysicsSimulation_tests PRIVATE ../include)
# Include Google Test headers
target_include_directories(PhysicsSimulation_tests PRIVATE ${googletest_SOURCE_DIR}/googletest/include ${googletest_SOURCE_DIR}/googlemock/include)

# Link test executable against Google Test libraries
target_link_libraries(PhysicsSimulation_tests PRIVATE gtest gtest_main gmock)

# Discover and add tests to CTest
include(GoogleTest)
gtest_discover_tests(PhysicsSimulation_tests)