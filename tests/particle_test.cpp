/**
 * @file particle_test.cpp
 * @brief Unit tests for the Particle class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-12
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h" // Include for Vector3 comparisons
#include "test_utils.h" // Include the shared helper functions
#include <cmath>   // For std::fabs
#include <limits>  // For std::numeric_limits

// Test fixture for Particle tests (optional for these tests, but good practice)
class ParticleTest : public ::testing::Test {
protected:
    // No common setup needed for these specific tests, but SetUp() could go here.
    Particle p; // Can create a particle instance here if needed across multiple tests
};

// Test the default constructor and initial state
TEST_F(ParticleTest, DefaultConstructor) {
    Particle default_p; // Use a local instance for clarity
    EXPECT_FLOAT_EQ(default_p._mass, 1.0f);
    EXPECT_FLOAT_EQ(default_p._radius, 0.1f);
    EXPECT_TRUE(AreVectorsClose(default_p._currPosition, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(default_p._prevPosition, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(default_p._currVelocity, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(default_p._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_FLOAT_EQ(default_p._red, 1.0f);
    EXPECT_FLOAT_EQ(default_p._green, 1.0f);
    EXPECT_FLOAT_EQ(default_p._blue, 1.0f);
    EXPECT_EQ(default_p._particleType, Particle::ACTIVE);
    // Test Update doesn't crash (basic check)
    // default_p.Update(); // No state change expected, just ensure it runs
    SUCCEED(); // Explicitly mark success if no assertions failed
}

// Test initialization with position only (zero velocity)
TEST_F(ParticleTest, InitializePositionOnly) {
    p.Initialize(
        5.0f,  // mass
        0.5f,  // radius
        1.0f, 2.0f, 3.0f, // position
        0.8f, 0.6f, 0.4f, // color
        Particle::PASSIVE // type
    );

    EXPECT_FLOAT_EQ(p._mass, 5.0f);
    EXPECT_FLOAT_EQ(p._radius, 0.5f);
    EXPECT_TRUE(AreVectorsClose(p._currPosition, Vector3(1.0f, 2.0f, 3.0f)));
    EXPECT_TRUE(AreVectorsClose(p._prevPosition, Vector3(1.0f, 2.0f, 3.0f))); // prev = initial curr
    EXPECT_TRUE(AreVectorsClose(p._currVelocity, Vector3(0.0f, 0.0f, 0.0f))); // Velocity should be zero
    EXPECT_TRUE(AreVectorsClose(p._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_FLOAT_EQ(p._red, 0.8f);
    EXPECT_FLOAT_EQ(p._green, 0.6f);
    EXPECT_FLOAT_EQ(p._blue, 0.4f);
    EXPECT_EQ(p._particleType, Particle::PASSIVE);
}

// Test initialization with position and velocity
TEST_F(ParticleTest, InitializePositionVelocity) {
    p.Initialize(
        10.0f, // mass
        1.5f,  // radius
        -1.0f, -2.0f, -3.0f, // position
        5.0f, 6.0f, 7.0f,    // velocity
        0.1f, 0.2f, 0.3f,    // color
        Particle::ACTIVE     // type
    );

    EXPECT_FLOAT_EQ(p._mass, 10.0f);
    EXPECT_FLOAT_EQ(p._radius, 1.5f);
    EXPECT_TRUE(AreVectorsClose(p._currPosition, Vector3(-1.0f, -2.0f, -3.0f)));
    EXPECT_TRUE(AreVectorsClose(p._prevPosition, Vector3(-1.0f, -2.0f, -3.0f))); // prev = initial curr
    EXPECT_TRUE(AreVectorsClose(p._currVelocity, Vector3(5.0f, 6.0f, 7.0f)));
    EXPECT_TRUE(AreVectorsClose(p._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_FLOAT_EQ(p._red, 0.1f);
    EXPECT_FLOAT_EQ(p._green, 0.2f);
    EXPECT_FLOAT_EQ(p._blue, 0.3f);
    EXPECT_EQ(p._particleType, Particle::ACTIVE);
}

// Test the ResetForces method
TEST_F(ParticleTest, ResetForces) {
    // Set some non-zero initial force
    p._resultantForce.Set(10.0f, 20.0f, 30.0f);
    ASSERT_FALSE(AreVectorsClose(p._resultantForce, Vector3(0.0f, 0.0f, 0.0f))); // Ensure it's not already zero

    p.ResetForces();
    EXPECT_TRUE(AreVectorsClose(p._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
}

// Note: Testing DrawPoint and DrawSphere would require mocking the Graphics dependency,
// which is more involved and typically done using a mocking framework alongside Google Test.
// Testing Update() would require a specific integration scheme to be implemented first.