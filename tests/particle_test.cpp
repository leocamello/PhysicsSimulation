/**
 * @file particle_test.cpp
 * @brief Unit tests for the Particle class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13 // Updated date
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h" // Include for Vector3 comparisons
#include "test_utils.h" // Include the shared helper functions
#include <cmath>   // For std::fabs
#include <limits>  // For std::numeric_limits

namespace PhysicsSimulation { // <-- Add namespace

// Test the default constructor and initial state
TEST(ParticleTest, DefaultConstructor) { // Changed from TEST_F to TEST
    Particle p; // Use a local instance

    // Check default values using getters
    EXPECT_FLOAT_EQ(p.mass(), 0.0f); // Default mass is now 0.0f
    EXPECT_FLOAT_EQ(p.radius(), 0.1f);
    EXPECT_TRUE(AreVectorsClose(p.position(), Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p.previous_position(), Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p.velocity(), Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p.color(), Vector3(1.0f, 1.0f, 1.0f))); // Check color vector
    EXPECT_EQ(p.type(), Particle::Type::kActive); // Check type enum class
}

// Test the parameterized constructor with position only (velocity defaults to zero)
TEST(ParticleTest, ConstructorPositionOnly) { // Renamed test
    const float mass = 5.0f;
    const float radius = 0.5f;
    const Vector3 pos(1.0f, 2.0f, 3.0f);
    const Vector3 color(0.8f, 0.6f, 0.4f);
    const Particle::Type type = Particle::Type::kFixed; // Assuming PASSIVE meant kFixed

    // Use parameterized constructor - velocity defaults to zero
    Particle p(mass, radius, pos, Vector3(), color, type);

    EXPECT_FLOAT_EQ(p.mass(), mass);
    EXPECT_FLOAT_EQ(p.radius(), radius);
    EXPECT_TRUE(AreVectorsClose(p.position(), pos));
    EXPECT_TRUE(AreVectorsClose(p.previous_position(), pos)); // prev = initial pos
    EXPECT_TRUE(AreVectorsClose(p.velocity(), Vector3(0.0f, 0.0f, 0.0f))); // Velocity should be zero
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p.color(), color));
    EXPECT_EQ(p.type(), type);
}

// Test the parameterized constructor with position and velocity
TEST(ParticleTest, ConstructorPositionVelocity) { // Renamed test
    const float mass = 10.0f;
    const float radius = 1.5f;
    const Vector3 pos(-1.0f, -2.0f, -3.0f);
    const Vector3 vel(5.0f, 6.0f, 7.0f);
    const Vector3 color(0.1f, 0.2f, 0.3f);
    const Particle::Type type = Particle::Type::kActive;

    // Use parameterized constructor
    Particle p(mass, radius, pos, vel, color, type);

    EXPECT_FLOAT_EQ(p.mass(), mass);
    EXPECT_FLOAT_EQ(p.radius(), radius);
    EXPECT_TRUE(AreVectorsClose(p.position(), pos));
    EXPECT_TRUE(AreVectorsClose(p.previous_position(), pos)); // prev = initial pos
    EXPECT_TRUE(AreVectorsClose(p.velocity(), vel));
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p.color(), color));
    EXPECT_EQ(p.type(), type);
}

// Test the AddForce method
TEST(ParticleTest, AddForce) {
    Particle p; // Default particle
    Vector3 force1(1.0f, 2.0f, 3.0f);
    Vector3 force2(-0.5f, 0.5f, -1.5f);
    Vector3 expected_total_force = force1 + force2;

    p.AddForce(force1);
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), force1));

    p.AddForce(force2);
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), expected_total_force));
}

// Test AddForce on a kFixed particle (should do nothing)
TEST(ParticleTest, AddForceFixedParticle) {
    Particle p(1.0f, 0.1f, Vector3(), Vector3(), Vector3(1,1,1), Particle::Type::kFixed);
    Vector3 force(10.0f, 20.0f, 30.0f);

    p.AddForce(force);
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
}


// Test the ClearForceAccumulator method
TEST(ParticleTest, ClearForceAccumulator) { // Renamed test
    Particle p;
    Vector3 initial_force(10.0f, 20.0f, 30.0f);

    // Use AddForce to set a non-zero initial force
    p.AddForce(initial_force);
    ASSERT_FALSE(AreVectorsClose(p.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f))); // Ensure it's not already zero

    p.ClearForceAccumulator(); // Call the method to test
    EXPECT_TRUE(AreVectorsClose(p.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
}

// Test Setters (Example for position and type)
TEST(ParticleTest, Setters) {
    Particle p;
    Vector3 new_pos(5.0f, 5.0f, 5.0f);
    Vector3 new_vel(1.0f, 1.0f, 1.0f);
    Vector3 new_color(0.5f, 0.5f, 0.5f);

    p.set_position(new_pos);
    EXPECT_TRUE(AreVectorsClose(p.position(), new_pos));

    p.set_velocity(new_vel);
    EXPECT_TRUE(AreVectorsClose(p.velocity(), new_vel));

    p.set_color(new_color);
    EXPECT_TRUE(AreVectorsClose(p.color(), new_color));

    p.set_type(Particle::Type::kFixed);
    EXPECT_EQ(p.type(), Particle::Type::kFixed);

    p.set_mass(100.0f);
    EXPECT_FLOAT_EQ(p.mass(), 100.0f);

    p.set_radius(1.0f);
    EXPECT_FLOAT_EQ(p.radius(), 1.0f);
}


// Note: Testing Draw() would require mocking the Graphics dependency.

} // namespace PhysicsSimulation <-- Close namespace