/**
 * @file gravity.h
 * @brief Defines the GravityForceGenerator class for applying a constant gravitational force.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_GRAVITY_FORCE_GENERATOR_H // Renamed include guard
#define PHYSICS_SIMULATION_GRAVITY_FORCE_GENERATOR_H

#include "PhysicsSimulation/forcegenerator.h" // Include the base class interface
#include "PhysicsSimulation/vector.h"         // Include Vector3 definition

// Forward declaration
class Particle;

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Applies a constant gravitational force (mass * acceleration) to particles.
 *
 * This force generator simulates a uniform gravitational field defined by an
 * acceleration vector (e.g., (0, -9.8, 0) for standard Earth gravity).
 */
class GravityForceGenerator : public ForceGenerator {
public:
    /**
     * @brief Constructor using a specific gravity acceleration vector.
     * @param acceleration The acceleration vector representing the gravitational field.
     */
    explicit GravityForceGenerator(const Vector3& acceleration) noexcept;

    /**
     * @brief Constructor using default Earth gravity (0, -9.8, 0).
     */
    GravityForceGenerator() noexcept;

    /**
     * @brief Default virtual destructor.
     */
    ~GravityForceGenerator() override = default;

    // --- Prevent Copying/Moving ---
    GravityForceGenerator(const GravityForceGenerator&) = delete;
    GravityForceGenerator& operator=(const GravityForceGenerator&) = delete;
    GravityForceGenerator(GravityForceGenerator&&) = delete;
    GravityForceGenerator& operator=(GravityForceGenerator&&) = delete;

    /**
     * @brief Applies the gravitational force (mass * acceleration_) to the particle.
     *
     * Adds the calculated force to the particle's resultant force.
     *
     * @param particle The particle to apply the force to.
     */
    void ApplyForce(Particle& particle) override;

    /**
     * @brief Sets the gravitational acceleration vector.
     * @param acceleration The new acceleration vector.
     */
    void set_acceleration(const Vector3& acceleration) noexcept;

    /**
     * @brief Gets the current gravitational acceleration vector.
     * @return The acceleration vector.
     */
    const Vector3& acceleration() const noexcept;

private:
    /** @brief The acceleration vector defining the gravitational field. */
    Vector3 acceleration_;
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_GRAVITY_FORCE_GENERATOR_H