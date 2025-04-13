/**
 * @file gravityforcegenerator_test.cpp
 * @brief Unit tests for the GravityForceGenerator class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/gravity.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"
#include "test_utils.h" // For AreVectorsClose

// Test fixture for GravityForceGenerator tests
class GravityForceGeneratorTest : public ::testing::Test {
protected:
    Particle particle_;
    const Vector3 default_gravity_ = Vector3(0.0f, -9.8f, 0.0f);
    const Vector3 custom_gravity_ = Vector3(0.0f, -1.62f, 0.0f); // Moon gravity approx
    const float particle_mass_ = 10.0f;

    void SetUp() override {
        // Initialize particle before each test
        particle_.Initialize(
            particle_mass_, 0.1f, // mass, radius
            0.0f, 100.0f, 0.0f,   // position
            0.0f, 0.0f, 0.0f,     // velocity
            1.0f, 1.0f, 1.0f,     // color
            Particle::ACTIVE
        );
        // Ensure forces are reset before each test
        particle_.ResetForces();
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

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._resultantForce, expected_force));
}

// Test ApplyForce with custom gravity
TEST_F(GravityForceGeneratorTest, ApplyForceCustomGravity) {
    GravityForceGenerator generator(custom_gravity_);
    generator.ApplyForce(particle_);

    Vector3 expected_force = custom_gravity_ * particle_mass_;

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._resultantForce, expected_force));
}

// Test that ApplyForce adds to existing forces
TEST_F(GravityForceGeneratorTest, ApplyForceAddsToExisting) {
    GravityForceGenerator generator; // Uses default gravity
    Vector3 initial_force(10.0f, 0.0f, 5.0f);
    // TODO: Update member access once Particle is refactored
    particle_._resultantForce = initial_force; // Set an initial force

    generator.ApplyForce(particle_);

    Vector3 expected_gravity_force = default_gravity_ * particle_mass_;
    Vector3 expected_total_force = initial_force + expected_gravity_force;

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._resultantForce, expected_total_force));
}

// Test ApplyForce with zero mass particle
TEST_F(GravityForceGeneratorTest, ApplyForceZeroMass) {
    GravityForceGenerator generator;
    // TODO: Update member access once Particle is refactored
    particle_._mass = 0.0f; // Set mass to zero
    particle_.ResetForces(); // Ensure force starts at zero

    generator.ApplyForce(particle_);

    // Expected: Force should remain zero
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
}

// Test ApplyForce with negative mass particle
TEST_F(GravityForceGeneratorTest, ApplyForceNegativeMass) {
    GravityForceGenerator generator;
    // TODO: Update member access once Particle is refactored
    particle_._mass = -10.0f; // Set mass to negative
    particle_.ResetForces(); // Ensure force starts at zero

    generator.ApplyForce(particle_);

    // Expected: Force should remain zero
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
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