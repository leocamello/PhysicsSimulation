/**
 * @file particlegenerator.h
 * @brief Defines the ParticleGenerator class for creating and managing particles.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_PARTICLE_GENERATOR_H
#define PHYSICS_SIMULATION_PARTICLE_GENERATOR_H

#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition
#include <vector>                       // For std::vector
#include <memory>                       // For std::unique_ptr
#include <random>                       // For random number generation

//namespace PhysicsSimulation {

/**
 * @brief Generates and manages a collection of particles.
 *
 * Creates particles with randomized properties within specified ranges
 * around a generation point. Manages particles using unique pointers.
 */
class ParticleGenerator {
public:
    /**
     * @brief Constructs and initializes the particle generator.
     *
     * @param mass The default mass for generated particles.
     * @param radius The default radius for generated particles.
     * @param initial_count The number of particles to generate initially.
     * @param generation_center The center position around which particles are generated.
     * @param generation_range_xy The half-range for random position offsets in X and Z.
     * @param generation_range_y The full range for random position offsets in Y (typically positive).
     */
    ParticleGenerator(float mass, float radius, size_t initial_count,
                      const Vector3& generation_center,
                      float generation_range_xz = 2.0f,
                      float generation_range_y = 500.0f) noexcept;

    /**
     * @brief Default virtual destructor.
     */
    virtual ~ParticleGenerator() = default;

    // --- Prevent Copying ---
    ParticleGenerator(const ParticleGenerator&) = delete;
    ParticleGenerator& operator=(const ParticleGenerator&) = delete;

    // --- Allow Moving ---
    ParticleGenerator(ParticleGenerator&&) noexcept = default;
    ParticleGenerator& operator=(ParticleGenerator&&) noexcept = default;

    /**
     * @brief Updates the particle generator state (e.g., generate new particles over time).
     * @note Currently a placeholder.
     */
    void Update();

    // --- Accessors ---
    /**
     * @brief Gets the number of particles currently managed.
     * @return The number of particles.
     */
    size_t GetParticleCount() const noexcept { return particles_.size(); }

    /**
     * @brief Gets a constant reference to a particle by index.
     * @param index The index of the particle.
     * @return Constant reference to the particle.
     * @throws std::out_of_range if index is invalid.
     */
    const Particle& GetParticle(size_t index) const;

    /**
     * @brief Gets a non-constant reference to a particle by index.
     * @param index The index of the particle.
     * @return Reference to the particle.
     * @throws std::out_of_range if index is invalid.
     */
    Particle& GetParticle(size_t index);

    /**
     * @brief Gets a constant reference to the internal vector of particle pointers.
     * @return Constant reference to the vector.
     */
    const std::vector<std::unique_ptr<Particle>>& particles() const noexcept { return particles_; }

    /**
     * @brief Gets a non-constant reference to the internal vector of particle pointers.
     * @return Reference to the vector.
     */
    std::vector<std::unique_ptr<Particle>>& particles() noexcept { return particles_; }

private:
    // Member variables
    float default_mass_ = 1.0f;
    float default_radius_ = 0.1f;
    Vector3 generation_position_;
    float generation_range_xz_ = 2.0f;
    float generation_range_y_ = 500.0f;

    std::vector<std::unique_ptr<Particle>> particles_;

    // Random number generation members
    std::mt19937 random_engine_;
    std::uniform_real_distribution<float> uniform_dist_sym_;
    std::uniform_real_distribution<float> uniform_dist_pos_;
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_PARTICLE_GENERATOR_H