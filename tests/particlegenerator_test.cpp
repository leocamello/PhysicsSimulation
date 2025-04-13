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

namespace PhysicsSimulation {

// Test fixture for ParticleGenerator tests - Keep constants here
class ParticleGeneratorTest : public ::testing::Test {
protected:
    const float default_mass_ = 5.0f;
    const float default_radius_ = 0.5f;
    const size_t default_count_ = 10;
    const Vector3 default_pos_ = Vector3(10.0f, 20.0f, 30.0f);
    const float default_range_xz_ = 2.0f;
    const float default_range_y_ = 500.0f;
};

// Test the constructor and initial particle creation
TEST_F(ParticleGeneratorTest, ConstructorBasic) {
    ParticleGenerator generator(default_mass_, default_radius_, default_count_,
                                default_pos_, default_range_xz_, default_range_y_);

    EXPECT_EQ(generator.GetParticleCount(), default_count_);
    ASSERT_FALSE(generator.particles().empty());

    try {
        const Particle& p = generator.GetParticle(0);
        EXPECT_FLOAT_EQ(p.mass(), default_mass_);
        EXPECT_FLOAT_EQ(p.radius(), default_radius_);
        EXPECT_EQ(p.type(), Particle::Type::kActive);

        EXPECT_GE(p.position().x, default_pos_.x - default_range_xz_);
        EXPECT_LE(p.position().x, default_pos_.x + default_range_xz_);
        EXPECT_GE(p.position().y, default_pos_.y);
        EXPECT_LE(p.position().y, default_pos_.y + default_range_y_);
        EXPECT_GE(p.position().z, default_pos_.z - default_range_xz_);
        EXPECT_LE(p.position().z, default_pos_.z + default_range_xz_);

        EXPECT_GE(p.color().x, 0.0f);
        EXPECT_LE(p.color().x, 1.0f);
        EXPECT_GE(p.color().y, 0.0f);
        EXPECT_LE(p.color().y, 1.0f);
        EXPECT_GE(p.color().z, 0.0f);
        EXPECT_LE(p.color().z, 1.0f);

    } catch (const std::out_of_range& oor) {
        FAIL() << "GetParticle(0) threw out_of_range unexpectedly: " << oor.what();
    }

    try {
        const Particle& p_last = generator.GetParticle(default_count_ - 1);
        EXPECT_FLOAT_EQ(p_last.mass(), default_mass_);
        EXPECT_FLOAT_EQ(p_last.radius(), default_radius_);
        EXPECT_GE(p_last.position().x, default_pos_.x - default_range_xz_);
        EXPECT_LE(p_last.position().x, default_pos_.x + default_range_xz_);
        EXPECT_GE(p_last.position().y, default_pos_.y);
        EXPECT_LE(p_last.position().y, default_pos_.y + default_range_y_);
        EXPECT_GE(p_last.position().z, default_pos_.z - default_range_xz_);
        EXPECT_LE(p_last.position().z, default_pos_.z + default_range_xz_);
    } catch (const std::out_of_range& oor) {
        FAIL() << "GetParticle(last) threw out_of_range unexpectedly: " << oor.what();
    }
}

// Test constructor with zero count
TEST_F(ParticleGeneratorTest, ConstructorZeroCount) {
    ParticleGenerator generator(default_mass_, default_radius_, 0,
                                default_pos_, default_range_xz_, default_range_y_);
    EXPECT_EQ(generator.GetParticleCount(), 0);
    EXPECT_TRUE(generator.particles().empty());
}

// Test GetParticle with invalid index
TEST_F(ParticleGeneratorTest, GetParticleInvalidIndex) {
    ParticleGenerator generator(default_mass_, default_radius_, default_count_,
                                default_pos_, default_range_xz_, default_range_y_);

    const ParticleGenerator& const_gen = generator;
    EXPECT_THROW(const_gen.GetParticle(default_count_), std::out_of_range);
    EXPECT_THROW(const_gen.GetParticle(default_count_ + 10), std::out_of_range);

    EXPECT_THROW(generator.GetParticle(default_count_), std::out_of_range);
    EXPECT_THROW(generator.GetParticle(default_count_ + 10), std::out_of_range);
}

// Test particles() accessor
TEST_F(ParticleGeneratorTest, ParticlesAccessor) {
    ParticleGenerator generator(default_mass_, default_radius_, default_count_,
                                default_pos_, default_range_xz_, default_range_y_);

    const auto& particles_vec = generator.particles();
    EXPECT_EQ(particles_vec.size(), default_count_);
    EXPECT_EQ(particles_vec.size(), generator.GetParticleCount());

    if (default_count_ > 0) {
        EXPECT_EQ(particles_vec[0].get(), &generator.GetParticle(0));
    }
}

// Test Update (currently does nothing, just check for no crash)
TEST_F(ParticleGeneratorTest, UpdateNoOp) {
    ParticleGenerator generator(default_mass_, default_radius_, default_count_,
                                default_pos_, default_range_xz_, default_range_y_);
    EXPECT_NO_THROW(generator.Update());
    EXPECT_EQ(generator.GetParticleCount(), default_count_);
}

// Test Move Constructor
TEST_F(ParticleGeneratorTest, MoveConstructor) {
    ParticleGenerator generator(default_mass_, default_radius_, default_count_,
                                default_pos_, default_range_xz_, default_range_y_);
    Particle* p_ptr_before_move = nullptr;
    if (default_count_ > 0) {
        p_ptr_before_move = &generator.GetParticle(0);
    }

    ParticleGenerator moved_generator(std::move(generator));

    EXPECT_EQ(moved_generator.GetParticleCount(), default_count_);
    if (default_count_ > 0) {
        EXPECT_EQ(&moved_generator.GetParticle(0), p_ptr_before_move);
        EXPECT_FLOAT_EQ(moved_generator.GetParticle(0).mass(), default_mass_);
    }

    EXPECT_EQ(generator.GetParticleCount(), 0);
    EXPECT_TRUE(generator.particles().empty());
}

// Test Move Assignment Operator
TEST_F(ParticleGeneratorTest, MoveAssignment) {
    ParticleGenerator generator(default_mass_, default_radius_, default_count_,
                                default_pos_, default_range_xz_, default_range_y_);
    Particle* p_ptr_before_move = nullptr;
    if (default_count_ > 0) {
        p_ptr_before_move = &generator.GetParticle(0);
    }

    ParticleGenerator assigned_generator(1.0f, 0.1f, 2, Vector3(0, 0, 0), 1.0f, 1.0f);
    EXPECT_EQ(assigned_generator.GetParticleCount(), 2);

    assigned_generator = std::move(generator);

    EXPECT_EQ(assigned_generator.GetParticleCount(), default_count_);
    if (default_count_ > 0) {
        EXPECT_EQ(&assigned_generator.GetParticle(0), p_ptr_before_move);
        EXPECT_FLOAT_EQ(assigned_generator.GetParticle(0).mass(), default_mass_);
    }

    EXPECT_EQ(generator.GetParticleCount(), 0);
    EXPECT_TRUE(generator.particles().empty());
}

} // namespace PhysicsSimulation