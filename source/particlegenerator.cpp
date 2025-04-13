/**
 * @file particlegenerator.cpp
 * @brief Implements the ParticleGenerator class methods using modern C++.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/particlegenerator.h"

#include <stdexcept> // For std::out_of_range
#include <vector>
#include <memory>
#include <random>

// Constructor
ParticleGenerator::ParticleGenerator() noexcept
    : random_engine_(std::random_device{}()), // Seed the engine
      uniform_dist_sym_(-1.0f, 1.0f),
      uniform_dist_pos_(0.0f, 1.0f) {}

// Initialize
void ParticleGenerator::Initialize(
    float mass, float radius, size_t max_count,
    float x, float y, float z) {
    default_mass_ = mass;
    default_radius_ = radius;
    generation_position_.Set(x, y, z);

    // Clear existing particles and reserve space for new ones
    particles_.clear();
    particles_.reserve(max_count);

    for (size_t i = 0; i < max_count; ++i) {
        // Generate random properties using the distributions
        float r = uniform_dist_pos_(random_engine_); // [0, 1]
        float g = uniform_dist_pos_(random_engine_); // [0, 1]
        float b = uniform_dist_pos_(random_engine_); // [0, 1]

        // Generate random position offset from the generator's position
        // Original ranges: x/z = [-2, 2], y = [0, 500] relative to position
        // We use the distributions scaled by the desired range magnitude.
        float px = (uniform_dist_sym_(random_engine_) * 2.0f) + generation_position_.x; // [-2, 2] offset
        float py = (uniform_dist_pos_(random_engine_) * 500.0f) + generation_position_.y; // [0, 500] offset
        float pz = (uniform_dist_sym_(random_engine_) * 2.0f) + generation_position_.z; // [-2, 2] offset

        // Create a new particle managed by a unique_ptr and add it to the vector
        auto particle_ptr = std::make_unique<Particle>();
        particle_ptr->Initialize(
            default_mass_, default_radius_,
            px, py, pz,
            r, g, b,
            Particle::ParticleType::ACTIVE); // Assuming ACTIVE is desired

        particles_.emplace_back(std::move(particle_ptr));
    }
}

// Update (currently placeholder)
void ParticleGenerator::Update() {
    // TODO: Implement particle generation/update logic over time if needed.
    // Example: Add one new particle per update if below a certain limit
    /*
    const size_t kMaxRuntimeParticles = 200; // Example limit
    if (particles_.size() < kMaxRuntimeParticles) {
        float r = uniform_dist_pos_(random_engine_);
        float g = uniform_dist_pos_(random_engine_);
        float b = uniform_dist_pos_(random_engine_);
        float px = (uniform_dist_sym_(random_engine_) * 4.0f) + generation_position_.x;
        float py = (uniform_dist_pos_(random_engine_) * 25.0f) + generation_position_.y;
        float pz = (uniform_dist_sym_(random_engine_) * 4.0f) + generation_position_.z;

        auto particle_ptr = std::make_unique<Particle>();
        particle_ptr->Initialize(default_mass_, default_radius_, px, py, pz, r, g, b, Particle::ParticleType::ACTIVE);
        particles_.emplace_back(std::move(particle_ptr));
    }
    */
}

// GetParticle (const version)
const Particle& ParticleGenerator::GetParticle(size_t index) const {
    // vector::at() provides bounds checking and throws std::out_of_range
    return *particles_.at(index);
}

// GetParticle (non-const version)
Particle& ParticleGenerator::GetParticle(size_t index) {
    // vector::at() provides bounds checking and throws std::out_of_range
    return *particles_.at(index);
}
