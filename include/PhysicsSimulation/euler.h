/**
 * @file euler.h
 * @brief Defines the EulerIntegrator class, implementing the forward Euler method.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_EULER_H // Consistent include guard
#define PHYSICS_SIMULATION_EULER_H

#include "PhysicsSimulation/integrator.h" // Include the base class interface

// Forward declarations
struct Vector3;
class Particle;

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Implements the forward (explicit) Euler integration method.
 *
 * This is a simple first-order numerical integration method. It's easy to
 * implement but can be unstable and inaccurate for larger time steps.
 *
 * Updates position based on current velocity and velocity based on current acceleration.
 * p(t+dt) = p(t) + v(t) * dt
 * v(t+dt) = v(t) + a(t) * dt
 */
class EulerIntegrator : public Integrator {
public:
    /**
     * @brief Default constructor.
     */
    EulerIntegrator() = default;

    /**
     * @brief Default virtual destructor.
     */
    ~EulerIntegrator() override = default;

    // --- Prevent Copying/Moving (optional, but good practice for hierarchy) ---
    EulerIntegrator(const EulerIntegrator&) = delete;
    EulerIntegrator& operator=(const EulerIntegrator&) = delete;
    EulerIntegrator(EulerIntegrator&&) = delete;
    EulerIntegrator& operator=(EulerIntegrator&&) = delete;

    /**
     * @brief Integrates the particle's state using the forward Euler method.
     *
     * @param acceleration The constant acceleration acting on the particle during the time step.
     * @param particle The particle whose state (position, velocity) is to be updated.
     * @param dt The duration of the time step (delta time).
     */
    void Integrate(const Vector3& acceleration, Particle& particle, float dt) override;
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_EULER_H