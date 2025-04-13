/**
 * @file particlegenerator.h
 * @brief Defines the ParticleGenerator class for creating and managing particles.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_PARTICLE_GENERATOR_H
#define PHYSICS_SIMULATION_PARTICLE_GENERATOR_H

#include <vector>
#include <memory> // For std::unique_ptr
#include <random> // For modern C++ random number generation
#include <cstddef> // For size_t

#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/vector.h"

// TODO: Consider uncommenting and using this namespace
// namespace PhysicsSimulation {

/**
 * @brief Generates and manages a collection of Particle objects using modern C++.
 *
 * Initializes a specified number of particles with randomized properties
 * around a central position. Uses RAII for memory management and the C++
 * <random> library for pseudo-random number generation.
 */
class ParticleGenerator {
public:
    /**
     * @brief Constructor. Initializes the random number generator.
     */
    ParticleGenerator() noexcept;

    // Default destructor is sufficient due to RAII (vector and unique_ptr handle cleanup)
    ~ParticleGenerator() = default;

    // --- Disable Copying and Assignment (unique_ptr makes class non-copyable) ---
    ParticleGenerator(const ParticleGenerator&) = delete;
    ParticleGenerator& operator=(const ParticleGenerator&) = delete;
    // --- Allow Moving ---
    ParticleGenerator(ParticleGenerator&&) noexcept = default;
    ParticleGenerator& operator=(ParticleGenerator&&) noexcept = default;

    /**
     * @brief Initializes the generator and creates the initial set of particles.
     *
     * Clears any existing particles and generates 'max_count' new ones.
     *
     * @param mass The mass for each generated particle.
     * @param radius The radius for each generated particle.
     * @param max_count The number of particles to create.
     * @param x The central x-coordinate for particle generation.
     * @param y The central y-coordinate for particle generation.
     * @param z The central z-coordinate for particle generation.
     * @note Particles are created with random positions and colors around (x, y, z).
     */
    void Initialize(float mass, float radius, size_t max_count, float x, float y, float z);

    /**
     * @brief Updates the state of the generator (currently placeholder).
     * @todo Implement particle generation/update logic over time if needed.
     */
    void Update();

    /**
     * @brief Gets the number of particles currently managed by the generator.
     * @return The number of particles.
     */
    size_t GetParticleCount() const noexcept { return particles_.size(); }

    /**
     * @brief Provides access to the vector of particle unique pointers.
     * @return A constant reference to the internal vector of particle pointers.
     * @warning Use with care. Modifying the unique_ptr outside the generator
     *          can lead to issues. Prefer accessing particles via GetParticle().
     */
    const std::vector<std::unique_ptr<Particle>>& GetParticles() const noexcept {
        return particles_;
    }

    /**
     * @brief Provides access to a specific particle by index.
     * @param index The index of the particle to retrieve.
     * @return A constant reference to the particle at the specified index.
     * @throws std::out_of_range if the index is invalid.
     */
    const Particle& GetParticle(size_t index) const;

    /**
     * @brief Provides access to a specific particle by index.
     * @param index The index of the particle to retrieve.
     * @return A reference to the particle at the specified index.
     * @throws std::out_of_range if the index is invalid.
     */
    Particle& GetParticle(size_t index);


private:
    /** @brief Default mass for generated particles. */
    float default_mass_ = 1.0f;
    /** @brief Default radius for generated particles. */
    float default_radius_ = 0.1f;
    /** @brief Central position for particle generation. */
    Vector3 generation_position_;

    /** @brief Container for the managed particle objects. */
    std::vector<std::unique_ptr<Particle>> particles_;

    /** @brief Random number engine. */
    std::mt19937 random_engine_;
    /** @brief Distribution for generating values roughly in [-1, 1]. */
    std::uniform_real_distribution<float> uniform_dist_sym_;
    /** @brief Distribution for generating values roughly in [0, 1]. */
    std::uniform_real_distribution<float> uniform_dist_pos_;
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_PARTICLE_GENERATOR_H