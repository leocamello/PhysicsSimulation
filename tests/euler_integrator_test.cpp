/**
 * @file euler_integrator_test.cpp
 * @brief Unit tests for the EulerIntegrator class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13
 */

#include <gtest/gtest.h>
#include "PhysicsSimulation/euler.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"
#include "test_utils.h" // For AreVectorsClose

// Test fixture for EulerIntegrator tests
class EulerIntegratorTest : public ::testing::Test {
protected:
    EulerIntegrator integrator_;
    Particle particle_;
    Vector3 initial_pos_ = Vector3(1.0f, 2.0f, 3.0f);
    Vector3 initial_vel_ = Vector3(10.0f, 0.0f, -5.0f);
    Vector3 acceleration_ = Vector3(0.0f, -9.8f, 0.0f); // Gravity
    float dt_ = 0.1f;

    void SetUp() override {
        // Initialize particle before each test
        particle_.Initialize(
            1.0f, 0.1f, // mass, radius
            initial_pos_.x, initial_pos_.y, initial_pos_.z, // position
            initial_vel_.x, initial_vel_.y, initial_vel_.z, // velocity
            1.0f, 1.0f, 1.0f, // color
            Particle::ACTIVE
        );
    }
};

// Test basic integration step
TEST_F(EulerIntegratorTest, IntegrateBasicStep) {
    integrator_.Integrate(acceleration_, particle_, dt_);

    // Expected values after one Euler step:
    // new_pos = old_pos + old_vel * dt
    Vector3 expected_pos = initial_pos_ + initial_vel_ * dt_;
    // new_vel = old_vel + acc * dt
    Vector3 expected_vel = initial_vel_ + acceleration_ * dt_;

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._currPosition, expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_._currVelocity, expected_vel));
}

// Test integration with zero acceleration
TEST_F(EulerIntegratorTest, IntegrateZeroAcceleration) {
    Vector3 zero_acc(0.0f, 0.0f, 0.0f);
    integrator_.Integrate(zero_acc, particle_, dt_);

    // Expected values: position changes by velocity, velocity remains constant
    Vector3 expected_pos = initial_pos_ + initial_vel_ * dt_;
    Vector3 expected_vel = initial_vel_; // Velocity shouldn't change

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._currPosition, expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_._currVelocity, expected_vel));
}

// Test integration with zero velocity
TEST_F(EulerIntegratorTest, IntegrateZeroVelocity) {
    particle_.Initialize(1.0f, 0.1f, initial_pos_.x, initial_pos_.y, initial_pos_.z, 0,0,0, 1,1,1, Particle::ACTIVE); // Zero velocity
    Vector3 zero_vel(0.0f, 0.0f, 0.0f);

    integrator_.Integrate(acceleration_, particle_, dt_);

    // Expected values: position remains constant (initially), velocity changes by acceleration
    Vector3 expected_pos = initial_pos_; // Position shouldn't change in the first step if velocity is zero
    Vector3 expected_vel = zero_vel + acceleration_ * dt_;

    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._currPosition, expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_._currVelocity, expected_vel));
}

// Test integration with zero time step
TEST_F(EulerIntegratorTest, IntegrateZeroDeltaTime) {
    integrator_.Integrate(acceleration_, particle_, 0.0f);

    // Expected: No change in position or velocity
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._currPosition, initial_pos_));
    EXPECT_TRUE(AreVectorsClose(particle_._currVelocity, initial_vel_));
}

// Test integration with negative time step (should do nothing)
TEST_F(EulerIntegratorTest, IntegrateNegativeDeltaTime) {
    integrator_.Integrate(acceleration_, particle_, -0.1f);

    // Expected: No change in position or velocity
    // TODO: Update member access once Particle is refactored
    EXPECT_TRUE(AreVectorsClose(particle_._currPosition, initial_pos_));
    EXPECT_TRUE(AreVectorsClose(particle_._currVelocity, initial_vel_));
}