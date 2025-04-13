/**
 * @file particlegenerator_test.cpp
 * @brief Unit tests for the ParticleGenerator class using Google Test.
 * @author GitHub Copilot
 * @date 2025-04-13
 */

#include <gtest/gtest.h>
#include <stdexcept> // For std::out_of_range
#include <vector>
#include <memory>

#include "PhysicsSimulation/particlegenerator.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"
#include "test_utils.h" // Assuming this contains AreFloatsClose, AreVectorsClose

// Test fixture for ParticleGenerator tests
class ParticleGeneratorTest : public ::testing::Test {
protected:
    ParticleGenerator generator_;
    const float default_mass_ = 5.0f;
    const float default_radius_ = 0.5f;
    const size_t default_count_ = 10;
    const Vector3 default_pos_ = Vector3(10.0f, 20.0f, 30.0f);
};

// Test the default constructor state
TEST_F(ParticleGeneratorTest, DefaultConstructor) {
    EXPECT_EQ(generator_.GetParticleCount(), 0);
    // Check if GetParticles returns an empty vector
    EXPECT_TRUE(generator_.GetParticles().empty());
}

// Test the Initialize method
TEST_F(ParticleGeneratorTest, InitializeBasic) {
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);

    EXPECT_EQ(generator_.GetParticleCount(), default_count_);
    ASSERT_FALSE(generator_.GetParticles().empty()); // Ensure vector is not empty before accessing

    // Check properties of the first particle (index 0)
    try {
        const Particle& p = generator_.GetParticle(0);
        EXPECT_FLOAT_EQ(p._mass, default_mass_);
        EXPECT_FLOAT_EQ(p._radius, default_radius_);
        EXPECT_EQ(p._particleType, Particle::ParticleType::ACTIVE);

        // Check position bounds (relative to generation position)
        // x/z offset: [-2, 2] -> pos.x/z should be in [default_pos_.x/z - 2, default_pos_.x/z + 2]
        // y offset: [0, 500] -> pos.y should be in [default_pos_.y, default_pos_.y + 500]
        EXPECT_GE(p._currPosition.x, default_pos_.x - 2.0f);
        EXPECT_LE(p._currPosition.x, default_pos_.x + 2.0f);
        EXPECT_GE(p._currPosition.y, default_pos_.y);
        EXPECT_LE(p._currPosition.y, default_pos_.y + 500.0f);
        EXPECT_GE(p._currPosition.z, default_pos_.z - 2.0f);
        EXPECT_LE(p._currPosition.z, default_pos_.z + 2.0f);

        // Check color bounds [0, 1]
        EXPECT_GE(p._red, 0.0f);
        EXPECT_LE(p._red, 1.0f);
        EXPECT_GE(p._green, 0.0f);
        EXPECT_LE(p._green, 1.0f);
        EXPECT_GE(p._blue, 0.0f);
        EXPECT_LE(p._blue, 1.0f);

    } catch (const std::out_of_range& oor) {
        FAIL() << "GetParticle(0) threw out_of_range unexpectedly: " << oor.what();
    }

     // Check properties of the last particle (index count - 1)
    try {
        const Particle& p_last = generator_.GetParticle(default_count_ - 1);
        EXPECT_FLOAT_EQ(p_last._mass, default_mass_);
        EXPECT_FLOAT_EQ(p_last._radius, default_radius_);
         // Check position bounds
        EXPECT_GE(p_last._currPosition.x, default_pos_.x - 2.0f);
        EXPECT_LE(p_last._currPosition.x, default_pos_.x + 2.0f);
        EXPECT_GE(p_last._currPosition.y, default_pos_.y);
        EXPECT_LE(p_last._currPosition.y, default_pos_.y + 500.0f);
        EXPECT_GE(p_last._currPosition.z, default_pos_.z - 2.0f);
        EXPECT_LE(p_last._currPosition.z, default_pos_.z + 2.0f);
    } catch (const std::out_of_range& oor) {
        FAIL() << "GetParticle(last) threw out_of_range unexpectedly: " << oor.what();
    }
}

// Test Initialize with zero count
TEST_F(ParticleGeneratorTest, InitializeZeroCount) {
    generator_.Initialize(default_mass_, default_radius_, 0,
                          default_pos_.x, default_pos_.y, default_pos_.z);
    EXPECT_EQ(generator_.GetParticleCount(), 0);
    EXPECT_TRUE(generator_.GetParticles().empty());
}

// Test that Initialize clears previous particles
TEST_F(ParticleGeneratorTest, InitializeReinitializes) {
    // First initialization
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);
    EXPECT_EQ(generator_.GetParticleCount(), default_count_);

    // Second initialization with different parameters
    size_t new_count = 5;
    float new_mass = 100.0f;
    generator_.Initialize(new_mass, default_radius_, new_count,
                          default_pos_.x, default_pos_.y, default_pos_.z);

    EXPECT_EQ(generator_.GetParticleCount(), new_count);
    ASSERT_FALSE(generator_.GetParticles().empty());

    // Check properties reflect the second initialization
    try {
        const Particle& p = generator_.GetParticle(0);
        EXPECT_FLOAT_EQ(p._mass, new_mass); // Check mass from second init
    } catch (const std::out_of_range& oor) {
        FAIL() << "GetParticle(0) after re-init threw out_of_range: " << oor.what();
    }
}

// Test GetParticle with invalid index
TEST_F(ParticleGeneratorTest, GetParticleInvalidIndex) {
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);

    // Test const version
    const ParticleGenerator& const_gen = generator_;
    EXPECT_THROW(const_gen.GetParticle(default_count_), std::out_of_range);
    EXPECT_THROW(const_gen.GetParticle(default_count_ + 10), std::out_of_range);

    // Test non-const version
    EXPECT_THROW(generator_.GetParticle(default_count_), std::out_of_range);
    EXPECT_THROW(generator_.GetParticle(default_count_ + 10), std::out_of_range);
}

// Test GetParticles accessor
TEST_F(ParticleGeneratorTest, GetParticles) {
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);

    const auto& particles_vec = generator_.GetParticles();
    EXPECT_EQ(particles_vec.size(), default_count_);
    EXPECT_EQ(particles_vec.size(), generator_.GetParticleCount());

    // Check if the pointer in the vector matches GetParticle
    if (default_count_ > 0) {
         EXPECT_EQ(particles_vec[0].get(), &generator_.GetParticle(0));
    }
}

// Test Update (currently does nothing, just check for no crash)
TEST_F(ParticleGeneratorTest, UpdateNoOp) {
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);
    EXPECT_NO_THROW(generator_.Update());
    // Count should remain unchanged as Update is a placeholder
    EXPECT_EQ(generator_.GetParticleCount(), default_count_);
}

// Test Move Constructor
TEST_F(ParticleGeneratorTest, MoveConstructor) {
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);
    // Store a pointer to a particle before move to check later
    Particle* p_ptr_before_move = nullptr;
    if (default_count_ > 0) {
        p_ptr_before_move = &generator_.GetParticle(0);
    }


    ParticleGenerator moved_generator(std::move(generator_));

    // Check the new generator
    EXPECT_EQ(moved_generator.GetParticleCount(), default_count_);
    if (default_count_ > 0) {
        EXPECT_EQ(&moved_generator.GetParticle(0), p_ptr_before_move); // Pointer should be the same
        EXPECT_FLOAT_EQ(moved_generator.GetParticle(0)._mass, default_mass_);
    }


    // Check the old (moved-from) generator - should be empty or valid state
    // The standard guarantees the moved-from object is in a valid state,
    // often this means empty for containers.
    EXPECT_EQ(generator_.GetParticleCount(), 0);
    EXPECT_TRUE(generator_.GetParticles().empty());
}

// Test Move Assignment Operator
TEST_F(ParticleGeneratorTest, MoveAssignment) {
    generator_.Initialize(default_mass_, default_radius_, default_count_,
                          default_pos_.x, default_pos_.y, default_pos_.z);
    Particle* p_ptr_before_move = nullptr;
     if (default_count_ > 0) {
        p_ptr_before_move = &generator_.GetParticle(0);
    }


    ParticleGenerator assigned_generator;
    // Initialize assigned_generator to ensure assignment overwrites correctly
    assigned_generator.Initialize(1.0f, 0.1f, 2, 0, 0, 0);
    EXPECT_EQ(assigned_generator.GetParticleCount(), 2);

    assigned_generator = std::move(generator_);

    // Check the assigned generator
    EXPECT_EQ(assigned_generator.GetParticleCount(), default_count_);
     if (default_count_ > 0) {
        EXPECT_EQ(&assigned_generator.GetParticle(0), p_ptr_before_move);
        EXPECT_FLOAT_EQ(assigned_generator.GetParticle(0)._mass, default_mass_);
    }

    // Check the old (moved-from) generator
    EXPECT_EQ(generator_.GetParticleCount(), 0);
    EXPECT_TRUE(generator_.GetParticles().empty());
}