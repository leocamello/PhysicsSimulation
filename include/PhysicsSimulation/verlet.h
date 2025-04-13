/**
 * @file verlet.h
 * @brief Defines the VerletIntegrator class, implementing the velocity Verlet method.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_VERLET_H // Consistent include guard
#define PHYSICS_SIMULATION_VERLET_H

#include "PhysicsSimulation/integrator.h" // Include the base class interface

// Forward declarations
struct Vector3;
class Particle;

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Implements the position-based Verlet integration method.
 *
 * This is a second-order numerical integration method known for its stability
 * in simulations, especially those involving constraints. It directly calculates
 * the next position based on the current and previous positions and the current
 * acceleration, implicitly handling velocity.
 *
 * p(t+dt) = p(t) + (p(t) - p(t-dt)) * (1 - drag) + a(t) * dt * dt
 *
 * @note The drag term is applied simplistically in this version.
 */
class VerletIntegrator : public Integrator {
public:
    /**
     * @brief Constructor.
     * @param drag A dimensionless damping factor applied each step (0.0 to 1.0).
     *             Defaults to 0.01. Higher values increase damping.
     */
    explicit VerletIntegrator(float drag = 0.01f) noexcept;

    /**
     * @brief Default virtual destructor.
     */
    ~VerletIntegrator() override = default;

    // --- Prevent Copying/Moving ---
    VerletIntegrator(const VerletIntegrator&) = delete;
    VerletIntegrator& operator=(const VerletIntegrator&) = delete;
    VerletIntegrator(VerletIntegrator&&) = delete;
    VerletIntegrator& operator=(VerletIntegrator&&) = delete;

    /**
     * @brief Integrates the particle's state using the position Verlet method.
     *
     * Updates the particle's current and previous positions based on the
     * provided acceleration and time step.
     *
     * @param acceleration The constant acceleration acting on the particle during the time step.
     * @param particle The particle whose state (positions) is to be updated.
     * @param dt The duration of the time step (delta time).
     */
    void Integrate(const Vector3& acceleration, Particle& particle, float dt) override;

    /**
     * @brief Sets the drag factor.
     * @param drag The new drag factor (clamped between 0.0 and 1.0).
     */
    void set_drag(float drag) noexcept;

    /**
     * @brief Gets the current drag factor.
     * @return The drag factor.
     */
    float drag() const noexcept;

private:
    /** @brief Dimensionless damping factor applied per time step. */
    float drag_ = 0.01f;
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_VERLET_H