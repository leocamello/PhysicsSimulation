/**
 * @file spring_test.cpp
 * @brief Unit tests for the Spring class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/spring.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"
#include "test_utils.h" // For AreVectorsClose
#include <stdexcept>    // For std::invalid_argument
#include <memory>       // For std::make_unique (if managing particles here)

// Test fixture for Spring tests
class SpringTest : public ::testing::Test {
protected:
    // Use unique_ptr if managing particle lifetime here, or raw if managed elsewhere
    Particle p1_;
    Particle p2_;
    float stiffness_ = 100.0f;
    float damping_ = 5.0f;
    float rest_length_ = 1.0f;

    void SetUp() override {
        // Initialize particles before each test
        // TODO: Update member access once Particle is refactored
        p1_.Initialize(1.0f, 0.1f, 0.0f, 0.0f, 0.0f, 0,0,0, 1,1,1, Particle::ACTIVE);
        p2_.Initialize(1.0f, 0.1f, rest_length_, 0.0f, 0.0f, 0,0,0, 1,1,1, Particle::ACTIVE); // Start at rest length
        p1_.ResetForces();
        p2_.ResetForces();
    }
};

// --- Constructor Tests ---

TEST_F(SpringTest, ConstructorValidExplicitRestLength) {
    EXPECT_NO_THROW(Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_));
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);
    EXPECT_FLOAT_EQ(spring.stiffness(), stiffness_);
    EXPECT_FLOAT_EQ(spring.damping(), damping_);
    EXPECT_FLOAT_EQ(spring.rest_length(), rest_length_);
    EXPECT_EQ(spring.particle_a(), &p1_);
    EXPECT_EQ(spring.particle_b(), &p2_);
}

TEST_F(SpringTest, ConstructorValidCalculatedRestLength) {
    // Position p2 further away to test calculation
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(2.5f, 0.0f, 0.0f);
    float expected_calculated_rest_length = 2.5f;

    EXPECT_NO_THROW(Spring spring(stiffness_, damping_, &p1_, &p2_));
    Spring spring(stiffness_, damping_, &p1_, &p2_);
    EXPECT_FLOAT_EQ(spring.stiffness(), stiffness_);
    EXPECT_FLOAT_EQ(spring.damping(), damping_);
    EXPECT_FLOAT_EQ(spring.rest_length(), expected_calculated_rest_length);
    EXPECT_EQ(spring.particle_a(), &p1_);
    EXPECT_EQ(spring.particle_b(), &p2_);
}

TEST_F(SpringTest, ConstructorInvalidNullParticleA) {
    EXPECT_THROW(Spring(stiffness_, damping_, nullptr, &p2_, rest_length_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNullParticleB) {
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, nullptr, rest_length_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidSameParticle) {
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, &p1_, rest_length_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidZeroStiffness) {
    EXPECT_THROW(Spring(0.0f, damping_, &p1_, &p2_, rest_length_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNegativeStiffness) {
    EXPECT_THROW(Spring(-10.0f, damping_, &p1_, &p2_, rest_length_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNegativeDamping) {
    EXPECT_THROW(Spring(stiffness_, -1.0f, &p1_, &p2_, rest_length_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNegativeRestLength) {
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, &p2_, -1.0f), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorCalculatedRestLengthNearZero) {
    // Place particles very close
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(1e-7f, 0.0f, 0.0f);
    EXPECT_NO_THROW(Spring spring(stiffness_, damping_, &p1_, &p2_));
    Spring spring(stiffness_, damping_, &p1_, &p2_);
    // Check if rest length calculation handled near-zero case appropriately (e.g., clamped to 0)
    EXPECT_NEAR(spring.rest_length(), 0.0f, 1e-5f); // Allow small tolerance or check for exact 0.0f
}


// --- ApplyForce Tests ---

TEST_F(SpringTest, ApplyForceAtRest) {
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_); // Particles are at rest length
    spring.ApplyForce();

    // Expected: No force applied
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
}

TEST_F(SpringTest, ApplyForceStretchedNoDamping) {
    // Stretch the spring
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(rest_length_ + 0.5f, 0.0f, 0.0f);
    float stretch = 0.5f;
    Spring spring(stiffness_, 0.0f, &p1_, &p2_, rest_length_); // Zero damping

    spring.ApplyForce();

    // Expected force: F = -k * stretch
    float expected_magnitude = -stiffness_ * stretch; // Negative because it pulls inward
    Vector3 expected_force_p1(expected_magnitude, 0.0f, 0.0f); // Pulls p1 towards p2
    Vector3 expected_force_p2(-expected_magnitude, 0.0f, 0.0f); // Pulls p2 towards p1

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, expected_force_p1));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, expected_force_p2));
}

TEST_F(SpringTest, ApplyForceCompressedNoDamping) {
    // Compress the spring
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(rest_length_ - 0.3f, 0.0f, 0.0f);
    float compression = -0.3f; // Negative displacement
    Spring spring(stiffness_, 0.0f, &p1_, &p2_, rest_length_); // Zero damping

    spring.ApplyForce();

    // Expected force: F = -k * compression
    float expected_magnitude = -stiffness_ * compression; // Positive because it pushes outward
    Vector3 expected_force_p1(expected_magnitude, 0.0f, 0.0f); // Pushes p1 away from p2
    Vector3 expected_force_p2(-expected_magnitude, 0.0f, 0.0f); // Pushes p2 away from p1

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, expected_force_p1));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, expected_force_p2));
}

TEST_F(SpringTest, ApplyForceDampingMovingApart) {
    // Stretch the spring and give particles outward velocity
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(rest_length_ + 0.5f, 0.0f, 0.0f);
    p1_._currVelocity.Set(-1.0f, 0.0f, 0.0f); // Moving left
    p2_._currVelocity.Set(1.0f, 0.0f, 0.0f);  // Moving right
    float stretch = 0.5f;
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);

    spring.ApplyForce();

    // Calculate expected forces
    // Spring force (pulls inward)
    float spring_magnitude = -stiffness_ * stretch;
    // Damping force (opposes relative velocity)
    Vector3 relative_velocity = p1_._currVelocity - p2_._currVelocity; // (-2, 0, 0)
    Vector3 unit_direction = (p1_._currPosition - p2_._currPosition).Normalized(); // (-1, 0, 0) approx
    float velocity_along_direction = Dot(relative_velocity, unit_direction); // (-2)*(-1) = 2.0
    float damping_magnitude = -damping_ * velocity_along_direction; // -damping * 2.0 (opposes separation)

    float total_magnitude = spring_magnitude + damping_magnitude;
    Vector3 expected_force_p1 = unit_direction * total_magnitude;
    Vector3 expected_force_p2 = -expected_force_p1;

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, expected_force_p1));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, expected_force_p2));
}

TEST_F(SpringTest, ApplyForceDampingMovingTogether) {
    // Compress the spring and give particles inward velocity
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(rest_length_ - 0.3f, 0.0f, 0.0f);
    p1_._currVelocity.Set(1.0f, 0.0f, 0.0f); // Moving right
    p2_._currVelocity.Set(-1.0f, 0.0f, 0.0f); // Moving left
    float compression = -0.3f;
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);

    spring.ApplyForce();

    // Calculate expected forces
    // Spring force (pushes outward)
    float spring_magnitude = -stiffness_ * compression;
    // Damping force (opposes relative velocity)
    Vector3 relative_velocity = p1_._currVelocity - p2_._currVelocity; // (2, 0, 0)
    Vector3 unit_direction = (p1_._currPosition - p2_._currPosition).Normalized(); // (-1, 0, 0) approx
    float velocity_along_direction = Dot(relative_velocity, unit_direction); // (2)*(-1) = -2.0
    float damping_magnitude = -damping_ * velocity_along_direction; // -damping * (-2.0) (opposes compression)

    float total_magnitude = spring_magnitude + damping_magnitude;
    Vector3 expected_force_p1 = unit_direction * total_magnitude;
    Vector3 expected_force_p2 = -expected_force_p1;

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, expected_force_p1));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, expected_force_p2));
}

TEST_F(SpringTest, ApplyForceAddsToExisting) {
    Spring spring(stiffness_, 0.0f, &p1_, &p2_, rest_length_); // At rest, zero damping
    Vector3 initial_force_p1(10, 20, 30);
    Vector3 initial_force_p2(-5, -15, -25);
    // TODO: Update member access once Particle is refactored
    p1_._resultantForce = initial_force_p1;
    p2_._resultantForce = initial_force_p2;

    spring.ApplyForce(); // Should apply zero force since at rest

    // Expected: Forces remain unchanged
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, initial_force_p1));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, initial_force_p2));

    // Now stretch it and apply again
    // TODO: Update member access once Particle is refactored
    p2_._currPosition.Set(rest_length_ + 0.5f, 0.0f, 0.0f);
    float stretch = 0.5f;
    float expected_spring_magnitude = -stiffness_ * stretch;
    Vector3 spring_force_p1(expected_spring_magnitude, 0.0f, 0.0f);
    Vector3 spring_force_p2(-expected_spring_magnitude, 0.0f, 0.0f);

    spring.ApplyForce(); // Applies spring force

    // Expected: Initial forces + spring forces
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, initial_force_p1 + spring_force_p1));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, initial_force_p2 + spring_force_p2));
}

TEST_F(SpringTest, ApplyForceCoincidentParticles) {
    // Place particles at the same position
    // TODO: Update member access once Particle is refactored
    p2_._currPosition = p1_._currPosition;
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);

    spring.ApplyForce();

    // Expected: No force applied (division by zero avoided)
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(p1_._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(AreVectorsClose(p2_._resultantForce, Vector3(0.0f, 0.0f, 0.0f)));
}

// --- Accessor Tests ---
TEST_F(SpringTest, Accessors) {
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);
    EXPECT_FLOAT_EQ(spring.stiffness(), stiffness_);
    EXPECT_FLOAT_EQ(spring.damping(), damping_);
    EXPECT_FLOAT_EQ(spring.rest_length(), rest_length_);
    EXPECT_EQ(spring.particle_a(), &p1_);
    EXPECT_EQ(spring.particle_b(), &p2_);
}

// Note: Testing Draw() would require mocking the Graphics dependency.