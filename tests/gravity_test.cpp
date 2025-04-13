/**
 * @file gravity_test.cpp
 * @brief Unit tests for the GravityForceGenerator class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/gravity.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"
#include "test_utils.h" // For AreVectorsClose

namespace PhysicsSimulation {

// Test fixture for GravityForceGenerator tests
class GravityForceGeneratorTest : public ::testing::Test {
protected:
    Particle particle_; // Default construct, initialize in SetUp
    const Vector3 default_gravity_ = Vector3(0.0f, -9.8f, 0.0f);
    const Vector3 custom_gravity_ = Vector3(0.0f, -1.62f, 0.0f); // Moon gravity approx
    const float particle_mass_ = 10.0f;
    const Vector3 initial_pos_ = Vector3(0.0f, 100.0f, 0.0f);
    const Vector3 initial_vel_ = Vector3(0.0f, 0.0f, 0.0f);
    const Vector3 initial_color_ = Vector3(1.0f, 1.0f, 1.0f);
    const float initial_radius_ = 0.1f;

    void SetUp() override {
        // Initialize particle using constructor before each test
        particle_ = Particle(
            particle_mass_, initial_radius_,
            initial_pos_, initial_vel_,
            initial_color_, Particle::Type::kActive
        );
        // Ensure forces are reset before each test
        particle_.ClearForceAccumulator(); // Use new method name
    }
};

// Test the default constructor (Earth gravity)
TEST_F(GravityForceGeneratorTest, DefaultConstructor) {
    GravityForceGenerator generator;
    EXPECT_TRUE(AreVectorsClose(generator.acceleration(), default_gravity_));
}

// Test the constructor with custom acceleration
TEST_F(GravityForceGeneratorTest, CustomConstructor) {
    GravityForceGenerator generator(custom_gravity_);
    EXPECT_TRUE(AreVectorsClose(generator.acceleration(), custom_gravity_));
}

// Test ApplyForce with default gravity
TEST_F(GravityForceGeneratorTest, ApplyForceDefaultGravity) {
    GravityForceGenerator generator; // Uses default gravity
    generator.ApplyForce(particle_);

    Vector3 expected_force = default_gravity_ * particle_mass_;

    // Use getter for force accumulator
    EXPECT_TRUE(AreVectorsClose(particle_.force_accumulator(), expected_force));
}

// Test ApplyForce with custom gravity
TEST_F(GravityForceGeneratorTest, ApplyForceCustomGravity) {
    GravityForceGenerator generator(custom_gravity_);
    generator.ApplyForce(particle_);

    Vector3 expected_force = custom_gravity_ * particle_mass_;

    // Use getter for force accumulator
    EXPECT_TRUE(AreVectorsClose(particle_.force_accumulator(), expected_force));
}

// Test that ApplyForce adds to existing forces
TEST_F(GravityForceGeneratorTest, ApplyForceAddsToExisting) {
    GravityForceGenerator generator; // Uses default gravity
    Vector3 initial_force(10.0f, 0.0f, 5.0f);
    particle_.AddForce(initial_force); // Set an initial force using AddForce

    generator.ApplyForce(particle_);

    Vector3 expected_gravity_force = default_gravity_ * particle_mass_;
    Vector3 expected_total_force = initial_force + expected_gravity_force;

    // Use getter for force accumulator
    EXPECT_TRUE(AreVectorsClose(particle_.force_accumulator(), expected_total_force));
}

// Test ApplyForce with zero mass particle
TEST_F(GravityForceGeneratorTest, ApplyForceZeroMass) {
    GravityForceGenerator generator;
    // Create a new particle with zero mass for this test
    Particle zero_mass_particle(
        0.0f, initial_radius_, // Zero mass
        initial_pos_, initial_vel_, initial_color_, Particle::Type::kActive
    );
    zero_mass_particle.ClearForceAccumulator(); // Ensure force starts at zero

    generator.ApplyForce(zero_mass_particle);

    // Expected: Force should remain zero (as per GravityForceGenerator implementation)
    EXPECT_TRUE(AreVectorsClose(zero_mass_particle.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
}

// Test ApplyForce with negative mass particle
TEST_F(GravityForceGeneratorTest, ApplyForceNegativeMass) {
    GravityForceGenerator generator;
     // Create a new particle with negative mass for this test
    Particle negative_mass_particle(
        -10.0f, initial_radius_, // Negative mass
        initial_pos_, initial_vel_, initial_color_, Particle::Type::kActive
    );
    negative_mass_particle.ClearForceAccumulator(); // Ensure force starts at zero

    generator.ApplyForce(negative_mass_particle);

    // Expected: Force should remain zero (as per GravityForceGenerator implementation)
    EXPECT_TRUE(AreVectorsClose(negative_mass_particle.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f)));
}

// Test set_acceleration and acceleration methods
TEST_F(GravityForceGeneratorTest, SetAndGetAcceleration) {
    GravityForceGenerator generator; // Start with default
    EXPECT_TRUE(AreVectorsClose(generator.acceleration(), default_gravity_));

    generator.set_acceleration(custom_gravity_);
    EXPECT_TRUE(AreVectorsClose(generator.acceleration(), custom_gravity_));

    generator.set_acceleration(Vector3(0,0,0));
    EXPECT_TRUE(AreVectorsClose(generator.acceleration(), Vector3(0,0,0)));
}

} // namespace PhysicsSimulation