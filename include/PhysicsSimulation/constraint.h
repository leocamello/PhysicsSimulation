/**
 * @file constraint.h
 * @brief Defines the Constraint class representing a fixed distance constraint between two particles.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_CONSTRAINT_H
#define PHYSICS_SIMULATION_CONSTRAINT_H

#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition
#include <stdexcept> // For std::invalid_argument

//namespace PhysicsSimulation {

/**
 * @brief Represents a fixed distance constraint (a rigid rod) between two particles.
 *
 * This constraint attempts to maintain a fixed distance (`length_`) between
 * `particle_a_` and `particle_b_` by directly adjusting their positions.
 */
class Constraint {
public:
    /**
     * @brief Constructs a distance constraint between two particles.
     *
     * @param length The desired fixed distance between the particles. Must be non-negative.
     * @param particle_a Pointer to the first particle. Must not be null.
     * @param particle_b Pointer to the second particle. Must not be null and must be different from particle_a.
     * @throws std::invalid_argument if length is negative or particles are invalid/same.
     */
    Constraint(float length, Particle* particle_a, Particle* particle_b);

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Constraint() = default;

    // --- Prevent Copying ---
    Constraint(const Constraint&) = delete;
    Constraint& operator=(const Constraint&) = delete;

    // --- Allow Moving ---
    Constraint(Constraint&&) noexcept = default;
    Constraint& operator=(Constraint&&) noexcept = default;

    /**
     * @brief Enforces the distance constraint by adjusting particle positions.
     *
     * Calculates the current distance and applies corrections to move particles
     * towards the desired distance. Handles fixed particles appropriately.
     */
    void SatisfyConstraint();

    // --- Accessors (Getters) ---
    float length() const noexcept { return length_; }
    const Particle* particle_a() const noexcept { return particle_a_; }
    Particle* particle_a() noexcept { return particle_a_; } // Non-const version
    const Particle* particle_b() const noexcept { return particle_b_; }
    Particle* particle_b() noexcept { return particle_b_; } // Non-const version

private:
    float length_;          /**< The target fixed distance for the constraint. */
    Particle* particle_a_;  /**< Pointer to the first particle. */
    Particle* particle_b_;  /**< Pointer to the second particle. */

    // Note: _currLength, _direction, _moveVector from the original code
    // are calculated transiently within SatisfyConstraint and don't need
    // to be member variables.
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_CONSTRAINT_H