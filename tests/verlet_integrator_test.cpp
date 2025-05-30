/**
 * @file verlet_integrator_test.cpp
 * @brief Unit tests for the VerletIntegrator class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/verlet.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"
#include "test_utils.h" // For AreVectorsClose

namespace PhysicsSimulation {

// Test fixture for VerletIntegrator tests
class VerletIntegratorTest : public ::testing::Test {
protected:
    // Use default drag initially
    VerletIntegrator integrator_; // drag = 0.01f by default
    Particle particle_;
    Vector3 initial_pos_ = Vector3(1.0f, 2.0f, 3.0f);
    // For Verlet, we need a previous position to imply initial velocity
    // Let's assume initial_vel = (10, 0, -5) and dt = 0.1
    // initial_pos = prev_pos + initial_vel * dt => prev_pos = initial_pos - initial_vel * dt
    Vector3 initial_vel_ = Vector3(10.0f, 0.0f, -5.0f);
    float dt_ = 0.1f;
    Vector3 prev_pos_ = initial_pos_ - initial_vel_ * dt_; // Calculate consistent previous position

    Vector3 acceleration_ = Vector3(0.0f, -9.8f, 0.0f); // Gravity
    Vector3 initial_color_ = Vector3(1.0f, 1.0f, 1.0f);
    float initial_mass_ = 1.0f;
    float initial_radius_ = 0.1f;

    void SetUp() override {
        // Initialize particle using constructor before each test
        particle_ = Particle(
            initial_mass_, initial_radius_,
            initial_pos_, Vector3(), // Initial velocity in constructor is ignored by Verlet, but needed
            initial_color_, Particle::Type::kActive // Use new enum
        );
        // Manually set previous position for Verlet using a setter
        particle_.set_previous_position(prev_pos_);
    }
};

// Test basic integration step with default drag
TEST_F(VerletIntegratorTest, IntegrateBasicStepDefaultDrag) {
    float drag = integrator_.drag(); // Get default drag
    integrator_.Integrate(acceleration_, particle_, dt_);

    // Expected values after one Verlet step:
    // new_pos = old_pos + (old_pos - prev_pos) * (1 - drag) + acc * dt * dt
    Vector3 displacement = initial_pos_ - prev_pos_;
    Vector3 expected_pos = initial_pos_ + displacement * (1.0f - drag) + acceleration_ * (dt_ * dt_);

    // Use getters to access particle state
    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    // Check that previous position was updated correctly
    EXPECT_TRUE(AreVectorsClose(particle_.previous_position(), initial_pos_));
}

// Test integration step with custom drag
TEST_F(VerletIntegratorTest, IntegrateBasicStepCustomDrag) {
    float custom_drag = 0.05f;
    VerletIntegrator custom_integrator(custom_drag);
    ASSERT_FLOAT_EQ(custom_integrator.drag(), custom_drag);

    custom_integrator.Integrate(acceleration_, particle_, dt_);

    // Expected values after one Verlet step:
    Vector3 displacement = initial_pos_ - prev_pos_;
    Vector3 expected_pos = initial_pos_ + displacement * (1.0f - custom_drag) + acceleration_ * (dt_ * dt_);

    // Use getters
    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_.previous_position(), initial_pos_));
}

// Test integration with zero acceleration
TEST_F(VerletIntegratorTest, IntegrateZeroAcceleration) {
    Vector3 zero_acc(0.0f, 0.0f, 0.0f);
    float drag = integrator_.drag();
    integrator_.Integrate(zero_acc, particle_, dt_);

    // Expected: Continues moving with initial velocity (damped slightly by drag)
    Vector3 displacement = initial_pos_ - prev_pos_;
    Vector3 expected_pos = initial_pos_ + displacement * (1.0f - drag); // No acceleration term

    // Use getters
    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_.previous_position(), initial_pos_));
}

// Test integration with zero initial velocity (prev_pos == initial_pos)
TEST_F(VerletIntegratorTest, IntegrateZeroVelocity) {
    // Set previous = current for zero velocity using setter
    particle_.set_previous_position(initial_pos_);
    float drag = integrator_.drag();

    integrator_.Integrate(acceleration_, particle_, dt_);

    // Expected: Moves based only on acceleration
    Vector3 displacement = initial_pos_ - initial_pos_; // Zero displacement
    Vector3 expected_pos = initial_pos_ + displacement * (1.0f - drag) + acceleration_ * (dt_ * dt_);
    // Simplifies to: expected_pos = initial_pos_ + acceleration_ * (dt_ * dt_);

    // Use getters
    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_.previous_position(), initial_pos_));
}

// Test integration with zero time step
TEST_F(VerletIntegratorTest, IntegrateZeroDeltaTime) {
    integrator_.Integrate(acceleration_, particle_, 0.0f);

    // Expected: No change in position
    // Use getters
    EXPECT_TRUE(AreVectorsClose(particle_.position(), initial_pos_));
    EXPECT_TRUE(AreVectorsClose(particle_.previous_position(), prev_pos_)); // prevPosition also unchanged
}

// Test integration with very small time step (should do nothing based on epsilon check)
TEST_F(VerletIntegratorTest, IntegrateSmallDeltaTime) {
    integrator_.Integrate(acceleration_, particle_, 1e-10f);

    // Expected: No change in position
    // Use getters
    EXPECT_TRUE(AreVectorsClose(particle_.position(), initial_pos_));
    EXPECT_TRUE(AreVectorsClose(particle_.previous_position(), prev_pos_));
}

// Test drag setting and clamping (This test doesn't use the fixture)
TEST(VerletIntegratorStandaloneTest, DragSettingAndClamping) {
    // Test default drag
    VerletIntegrator integrator1;
    EXPECT_FLOAT_EQ(integrator1.drag(), 0.01f);

    // Test valid custom drag
    VerletIntegrator integrator2(0.5f);
    EXPECT_FLOAT_EQ(integrator2.drag(), 0.5f);

    // Test drag below zero (should clamp to 0)
    VerletIntegrator integrator3(-1.0f);
    EXPECT_FLOAT_EQ(integrator3.drag(), 0.0f);

    // Test drag above one (should clamp to 1)
    VerletIntegrator integrator4(2.0f);
    EXPECT_FLOAT_EQ(integrator4.drag(), 1.0f);

    // Test set_drag
    integrator1.set_drag(0.75f);
    EXPECT_FLOAT_EQ(integrator1.drag(), 0.75f);

    integrator1.set_drag(-0.5f);
    EXPECT_FLOAT_EQ(integrator1.drag(), 0.0f);

    integrator1.set_drag(1.5f);
    EXPECT_FLOAT_EQ(integrator1.drag(), 1.0f);
}

} // namespace PhysicsSimulation