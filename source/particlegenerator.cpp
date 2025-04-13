/**
 * @file particlegenerator.cpp
 * @brief Implements the ParticleGenerator class methods using modern C++.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/particlegenerator.h"
#include "PhysicsSimulation/particle.h" // Included via header
#include "PhysicsSimulation/vector.h"   // Included via header

#include <stdexcept> // For std::out_of_range
#include <vector>
#include <memory>
#include <random>
#include <cmath>     // For std::fabs (if needed later)

//namespace PhysicsSimulation {

// Constructor - Replaces Initialize
ParticleGenerator::ParticleGenerator(float mass, float radius, size_t initial_count,
                                     const Vector3& generation_center,
                                     float generation_range_xz,
                                     float generation_range_y) noexcept
    : default_mass_(mass),
      default_radius_(radius),
      generation_position_(generation_center), // Use Vector3 copy constructor
      generation_range_xz_(generation_range_xz),
      generation_range_y_(generation_range_y),
      random_engine_(std::random_device{}()), // Seed the engine
      uniform_dist_sym_(-1.0f, 1.0f),         // Base distribution [-1, 1]
      uniform_dist_pos_(0.0f, 1.0f)          // Base distribution [0, 1]
{
    // Reserve space for initial particles
    particles_.reserve(initial_count);

    // Generate initial particles
    for (size_t i = 0; i < initial_count; ++i) {
        // Generate random color components [0, 1]
        Vector3 color(uniform_dist_pos_(random_engine_),
                      uniform_dist_pos_(random_engine_),
                      uniform_dist_pos_(random_engine_));

        // Generate random position offset from the generator's position
        // Scale the base distributions by the desired range magnitude.
        float offset_x = uniform_dist_sym_(random_engine_) * generation_range_xz_; // [-range_xz, +range_xz]
        float offset_y = uniform_dist_pos_(random_engine_) * generation_range_y_;  // [0, range_y]
        float offset_z = uniform_dist_sym_(random_engine_) * generation_range_xz_; // [-range_xz, +range_xz]

        Vector3 position = generation_position_ + Vector3(offset_x, offset_y, offset_z);

        // Create a new particle using the Particle constructor within make_unique
        // Assuming default velocity is zero Vector3() and type is kActive
        particles_.emplace_back(std::make_unique<Particle>(
            default_mass_, default_radius_,
            position, Vector3(), // Position, Velocity (zero)
            color, Particle::Type::kActive // Color, Type
            ));
    }
}

// Destructor is defaulted in the header.

// Update (currently placeholder, updated commented code)
void ParticleGenerator::Update() {
    // TODO: Implement particle generation/update logic over time if needed.
    // Example: Add one new particle per update if below a certain limit
    /*
    const size_t kMaxRuntimeParticles = 200; // Example limit
    if (particles_.size() < kMaxRuntimeParticles) {
        Vector3 color(uniform_dist_pos_(random_engine_),
                      uniform_dist_pos_(random_engine_),
                      uniform_dist_pos_(random_engine_));

        float offset_x = uniform_dist_sym_(random_engine_) * generation_range_xz_;
        float offset_y = uniform_dist_pos_(random_engine_) * generation_range_y_;
        float offset_z = uniform_dist_sym_(random_engine_) * generation_range_xz_;
        Vector3 position = generation_position_ + Vector3(offset_x, offset_y, offset_z);

        // Use Particle constructor
        particles_.emplace_back(std::make_unique<Particle>(
            default_mass_, default_radius_,
            position, Vector3(), // Position, Velocity (zero)
            color, Particle::Type::kActive // Color, Type
        ));
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

//} // namespace PhysicsSimulation
