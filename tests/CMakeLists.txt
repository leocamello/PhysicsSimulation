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

# Add test executables
add_executable(vector_test vector_test.cpp)

# Link test executables against Google Test and your library/source files
# Ensure your main library target (e.g., PhysicsSimulationLib) is defined in the root CMakeLists.txt
# and includes the vector.h header (implicitly or explicitly).
target_link_libraries(vector_test PRIVATE gtest_main)

# Add tests to CTest
add_test(NAME Vector3Tests COMMAND vector_test)