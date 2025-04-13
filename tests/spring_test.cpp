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

namespace PhysicsSimulation {

// Test fixture for Spring tests
class SpringTest : public ::testing::Test {
protected:
    // Particles are default constructed, then properly initialized in SetUp
    Particle p1_;
    Particle p2_;
    float stiffness_ = 100.0f;
    float damping_ = 5.0f;
    float rest_length_ = 1.0f;
    Vector3 p1_initial_pos_ = Vector3(0.0f, 0.0f, 0.0f);
    Vector3 p2_initial_pos_ = Vector3(rest_length_, 0.0f, 0.0f); // Start at rest length

    void SetUp() override {
        // Initialize particles using constructor before each test
        p1_ = Particle(1.0f, 0.1f, p1_initial_pos_, Vector3(), Vector3(1,1,1), Particle::Type::kActive);
        p2_ = Particle(1.0f, 0.1f, p2_initial_pos_, Vector3(), Vector3(1,1,1), Particle::Type::kActive);
        p1_.ClearForceAccumulator(); // Use new method name
        p2_.ClearForceAccumulator(); // Use new method name
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
    Vector3 new_p2_pos(2.5f, 0.0f, 0.0f);
    p2_.set_position(new_p2_pos); // Use setter
    float expected_calculated_rest_length = (p1_.position() - new_p2_pos).Length();

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
    EXPECT_THROW(Spring(stiffness_, damping_, nullptr, &p2_), std::invalid_argument); // Test other constructor
}

TEST_F(SpringTest, ConstructorInvalidNullParticleB) {
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, nullptr, rest_length_), std::invalid_argument);
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, nullptr), std::invalid_argument); // Test other constructor
}

TEST_F(SpringTest, ConstructorInvalidSameParticle) {
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, &p1_, rest_length_), std::invalid_argument);
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, &p1_), std::invalid_argument); // Test other constructor
}

TEST_F(SpringTest, ConstructorInvalidZeroStiffness) {
    EXPECT_THROW(Spring(0.0f, damping_, &p1_, &p2_, rest_length_), std::invalid_argument);
    EXPECT_THROW(Spring(0.0f, damping_, &p1_, &p2_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNegativeStiffness) {
    EXPECT_THROW(Spring(-10.0f, damping_, &p1_, &p2_, rest_length_), std::invalid_argument);
    EXPECT_THROW(Spring(-10.0f, damping_, &p1_, &p2_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNegativeDamping) {
    EXPECT_THROW(Spring(stiffness_, -1.0f, &p1_, &p2_, rest_length_), std::invalid_argument);
    EXPECT_THROW(Spring(stiffness_, -1.0f, &p1_, &p2_), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorInvalidNegativeRestLength) {
    // Only applicable for the constructor that takes rest_length explicitly
    EXPECT_THROW(Spring(stiffness_, damping_, &p1_, &p2_, -1.0f), std::invalid_argument);
}

TEST_F(SpringTest, ConstructorCalculatedRestLengthNearZero) {
    // Place particles very close
    p2_.set_position(p1_.position() + Vector3(1e-7f, 0.0f, 0.0f)); // Use setter
    EXPECT_NO_THROW(Spring spring(stiffness_, damping_, &p1_, &p2_));
    Spring spring(stiffness_, damping_, &p1_, &p2_);
    // Check if rest length calculation handled near-zero case appropriately (clamped to 0)
    EXPECT_NEAR(spring.rest_length(), 0.0f, 1e-5f); // Allow small tolerance
}


// --- ApplyForce Tests ---

TEST_F(SpringTest, ApplyForceAtRest) {
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_); // Particles are at rest length
    spring.ApplyForce();

    // Expected: No force applied
    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f))); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f))); // Use getter
}

TEST_F(SpringTest, ApplyForceStretchedNoDamping) {
    // Stretch the spring
    float stretch = 0.5f;
    p2_.set_position(Vector3(rest_length_ + stretch, 0.0f, 0.0f)); // Use setter
    Spring spring(stiffness_, 0.0f, &p1_, &p2_, rest_length_); // Zero damping

    spring.ApplyForce();

    // Expected force: F = -k * stretch
    float expected_magnitude = -stiffness_ * stretch; // Negative because it pulls inward
    Vector3 expected_force_p1(-expected_magnitude, 0.0f, 0.0f); // Pulls p1 towards p2 (positive x)
    Vector3 expected_force_p2(expected_magnitude, 0.0f, 0.0f); // Pulls p2 towards p1 (negative x)

    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), expected_force_p1)); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), expected_force_p2)); // Use getter
}

TEST_F(SpringTest, ApplyForceCompressedNoDamping) {
    // Compress the spring
    float compression_dist = 0.3f;
    p2_.set_position(Vector3(rest_length_ - compression_dist, 0.0f, 0.0f)); // Use setter
    float displacement = -compression_dist; // Negative displacement
    Spring spring(stiffness_, 0.0f, &p1_, &p2_, rest_length_); // Zero damping

    spring.ApplyForce();

    // Expected force: F = -k * displacement
    float expected_magnitude = -stiffness_ * displacement; // Positive because it pushes outward
    Vector3 expected_force_p1(-expected_magnitude, 0.0f, 0.0f); // Pushes p1 away from p2 (negative x)
    Vector3 expected_force_p2(expected_magnitude, 0.0f, 0.0f); // Pushes p2 away from p1 (positive x)

    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), expected_force_p1)); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), expected_force_p2)); // Use getter
}

TEST_F(SpringTest, ApplyForceDampingMovingApart) {
    // Stretch the spring and give particles outward velocity
    float stretch = 0.5f;
    p2_.set_position(Vector3(rest_length_ + stretch, 0.0f, 0.0f)); // Use setter
    p1_.set_velocity(Vector3(-1.0f, 0.0f, 0.0f)); // Moving left
    p2_.set_velocity(Vector3(1.0f, 0.0f, 0.0f));  // Moving right
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);

    spring.ApplyForce();

    // Calculate expected forces
    // Spring force (pulls inward)
    float spring_magnitude = -stiffness_ * stretch;
    // Damping force (opposes relative velocity)
    Vector3 relative_velocity = p1_.velocity() - p2_.velocity(); // (-2, 0, 0) - Use getters
    Vector3 unit_direction = (p1_.position() - p2_.position()).Normalized(); // (-1, 0, 0) approx - Use getters
    float velocity_along_direction = Dot(relative_velocity, unit_direction); // (-2)*(-1) = 2.0
    float damping_magnitude = -damping_ * velocity_along_direction; // -damping * 2.0 (opposes separation)

    float total_magnitude = spring_magnitude + damping_magnitude;
    Vector3 expected_force_p1 = unit_direction * total_magnitude;
    Vector3 expected_force_p2 = -expected_force_p1;

    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), expected_force_p1)); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), expected_force_p2)); // Use getter
}

TEST_F(SpringTest, ApplyForceDampingMovingTogether) {
    // Compress the spring and give particles inward velocity
    float compression_dist = 0.3f;
    p2_.set_position(Vector3(rest_length_ - compression_dist, 0.0f, 0.0f)); // Use setter
    p1_.set_velocity(Vector3(1.0f, 0.0f, 0.0f)); // Moving right
    p2_.set_velocity(Vector3(-1.0f, 0.0f, 0.0f)); // Moving left
    float displacement = -compression_dist;
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);

    spring.ApplyForce();

    // Calculate expected forces
    // Spring force (pushes outward)
    float spring_magnitude = -stiffness_ * displacement;
    // Damping force (opposes relative velocity)
    Vector3 relative_velocity = p1_.velocity() - p2_.velocity(); // (2, 0, 0) - Use getters
    Vector3 unit_direction = (p1_.position() - p2_.position()).Normalized(); // (-1, 0, 0) approx - Use getters
    float velocity_along_direction = Dot(relative_velocity, unit_direction); // (2)*(-1) = -2.0
    float damping_magnitude = -damping_ * velocity_along_direction; // -damping * (-2.0) (opposes compression)

    float total_magnitude = spring_magnitude + damping_magnitude;
    Vector3 expected_force_p1 = unit_direction * total_magnitude;
    Vector3 expected_force_p2 = -expected_force_p1;

    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), expected_force_p1)); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), expected_force_p2)); // Use getter
}

TEST_F(SpringTest, ApplyForceAddsToExisting) {
    Spring spring(stiffness_, 0.0f, &p1_, &p2_, rest_length_); // At rest, zero damping
    Vector3 initial_force_p1(10, 20, 30);
    Vector3 initial_force_p2(-5, -15, -25);
    p1_.AddForce(initial_force_p1); // Use AddForce
    p2_.AddForce(initial_force_p2); // Use AddForce

    spring.ApplyForce(); // Should apply zero force since at rest

    // Expected: Forces remain unchanged
    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), initial_force_p1)); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), initial_force_p2)); // Use getter

    // Now stretch it and apply again
    float stretch = 0.5f;
    p2_.set_position(Vector3(rest_length_ + stretch, 0.0f, 0.0f)); // Use setter
    float expected_spring_magnitude = -stiffness_ * stretch;
    Vector3 spring_force_p1(-expected_spring_magnitude, 0.0f, 0.0f); // Force on p1 is in +x direction
    Vector3 spring_force_p2(expected_spring_magnitude, 0.0f, 0.0f); // Force on p2 is in -x direction

    spring.ApplyForce(); // Applies spring force

    // Expected: Initial forces + spring forces
    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), initial_force_p1 + spring_force_p1)); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), initial_force_p2 + spring_force_p2)); // Use getter
}

TEST_F(SpringTest, ApplyForceCoincidentParticles) {
    // Place particles at the same position
    p2_.set_position(p1_.position()); // Use setter
    Spring spring(stiffness_, damping_, &p1_, &p2_, rest_length_);

    spring.ApplyForce();

    // Expected: No force applied (division by zero avoided)
    EXPECT_TRUE(AreVectorsClose(p1_.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f))); // Use getter
    EXPECT_TRUE(AreVectorsClose(p2_.force_accumulator(), Vector3(0.0f, 0.0f, 0.0f))); // Use getter
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

} // namespace PhysicsSimulation