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

namespace PhysicsSimulation {

// Test fixture for EulerIntegrator tests
class EulerIntegratorTest : public ::testing::Test {
protected:
    EulerIntegrator integrator_;
    // Default construct particle, will be properly initialized in SetUp
    Particle particle_;
    Vector3 initial_pos_ = Vector3(1.0f, 2.0f, 3.0f);
    Vector3 initial_vel_ = Vector3(10.0f, 0.0f, -5.0f);
    Vector3 initial_color_ = Vector3(1.0f, 1.0f, 1.0f);
    float initial_mass_ = 1.0f;
    float initial_radius_ = 0.1f;
    Vector3 acceleration_ = Vector3(0.0f, -9.8f, 0.0f); // Gravity
    float dt_ = 0.1f;

    void SetUp() override {
        // Initialize particle using the constructor before each test
        particle_ = Particle(
            initial_mass_, initial_radius_,
            initial_pos_, initial_vel_,
            initial_color_, Particle::Type::kActive
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

    // Use getters to access particle state
    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_.velocity(), expected_vel));
}

// Test integration with zero acceleration
TEST_F(EulerIntegratorTest, IntegrateZeroAcceleration) {
    Vector3 zero_acc(0.0f, 0.0f, 0.0f);
    integrator_.Integrate(zero_acc, particle_, dt_);

    // Expected values: position changes by velocity, velocity remains constant
    Vector3 expected_pos = initial_pos_ + initial_vel_ * dt_;
    Vector3 expected_vel = initial_vel_; // Velocity shouldn't change

    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_.velocity(), expected_vel));
}

// Test integration with zero velocity
TEST_F(EulerIntegratorTest, IntegrateZeroVelocity) {
    // Re-initialize particle with zero velocity for this test
    Vector3 zero_vel(0.0f, 0.0f, 0.0f);
    particle_ = Particle(
        initial_mass_, initial_radius_,
        initial_pos_, zero_vel, // Use zero velocity
        initial_color_, Particle::Type::kActive
    );

    integrator_.Integrate(acceleration_, particle_, dt_);

    // Expected values: position remains constant (initially), velocity changes by acceleration
    Vector3 expected_pos = initial_pos_; // Position shouldn't change in the first step if velocity is zero
    Vector3 expected_vel = zero_vel + acceleration_ * dt_;

    EXPECT_TRUE(AreVectorsClose(particle_.position(), expected_pos));
    EXPECT_TRUE(AreVectorsClose(particle_.velocity(), expected_vel));
}

// Test integration with zero time step
TEST_F(EulerIntegratorTest, IntegrateZeroDeltaTime) {
    integrator_.Integrate(acceleration_, particle_, 0.0f);

    // Expected: No change in position or velocity
    EXPECT_TRUE(AreVectorsClose(particle_.position(), initial_pos_));
    EXPECT_TRUE(AreVectorsClose(particle_.velocity(), initial_vel_));
}

// Test integration with negative time step (should do nothing as per implementation)
TEST_F(EulerIntegratorTest, IntegrateNegativeDeltaTime) {
    integrator_.Integrate(acceleration_, particle_, -0.1f);

    // Expected: No change in position or velocity
    EXPECT_TRUE(AreVectorsClose(particle_.position(), initial_pos_));
    EXPECT_TRUE(AreVectorsClose(particle_.velocity(), initial_vel_));
}

} // namespace PhysicsSimulation