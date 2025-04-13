/**
 * @file medium.h
 * @brief Defines the Medium class representing a drag force generator.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_MEDIUM_H
#define PHYSICS_SIMULATION_MEDIUM_H

#include "PhysicsSimulation/forcegenerator.h" // Base class
#include "PhysicsSimulation/particle.h"       // For ApplyForce signature
#include "PhysicsSimulation/vector.h"         // For Vector3 usage in ApplyForce

//namespace PhysicsSimulation {

/**
 * @brief A force generator that applies a simple linear drag force.
 *
 * The drag force is calculated as F = -k * v, where k is the drag coefficient
 * and v is the particle's velocity.
 */
class Medium : public ForceGenerator {
public:
    /**
     * @brief Constructs a Medium with a specified drag coefficient.
     * @param drag_coefficient The linear drag coefficient (k). Must be non-negative.
     * @throws std::invalid_argument if drag_coefficient is negative.
     */
    explicit Medium(float drag_coefficient);

    /**
     * @brief Default virtual destructor.
     */
    ~Medium() override = default;

    // --- Prevent Copying/Moving (optional, depends on use case) ---
    // If Medium objects are managed by unique_ptr, moving might be useful.
    // If they are stored directly or by reference, copying might be needed.
    // For simplicity, let's prevent both for now unless needed.
    Medium(const Medium&) = delete;
    Medium& operator=(const Medium&) = delete;
    Medium(Medium&&) = delete;
    Medium& operator=(Medium&&) = delete;

    /**
     * @brief Applies the drag force to the given particle.
     *
     * Calculates F = -drag_coefficient_ * velocity and adds it to the
     * particle's force accumulator.
     * @param particle The particle to apply the force to.
     */
    void ApplyForce(Particle& particle) override;

    // --- Accessors ---
    float drag_coefficient() const noexcept { return drag_coefficient_; }

    // --- Mutators ---
    /**
     * @brief Sets the drag coefficient.
     * @param drag_coefficient The new drag coefficient. Must be non-negative.
     * @throws std::invalid_argument if drag_coefficient is negative.
     */
    void set_drag_coefficient(float drag_coefficient);

private:
    float drag_coefficient_ = 0.0f; /**< The linear drag coefficient (k). */
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_MEDIUM_H