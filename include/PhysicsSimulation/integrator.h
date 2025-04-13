/**
 * @file integrator.h
 * @brief Defines the abstract base class for numerical integration methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_INTEGRATOR_H // Consistent include guard
#define PHYSICS_SIMULATION_INTEGRATOR_H

// Forward declarations to minimize header dependencies
// #include "vector.h" // Not needed directly in the interface
// #include "particle.h" // Not needed directly in the interface
struct Vector3;
class Particle;

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Abstract base class defining the interface for numerical integrators.
 *
 * Derived classes implement specific algorithms (e.g., Euler, Verlet) to update
 * a particle's state based on its acceleration over a time step.
 */
class Integrator {
public:
    /**
     * @brief Virtual destructor. Essential for base classes with virtual functions.
     */
    virtual ~Integrator() = default;

    /**
     * @brief Integrates the particle's state forward by a given time step.
     *
     * Pure virtual function that must be implemented by derived classes.
     *
     * @param acceleration The constant acceleration acting on the particle during the time step.
     * @param particle The particle whose state (position, velocity) is to be updated.
     * @param dt The duration of the time step (delta time).
     */
    virtual void Integrate(const Vector3& acceleration, Particle& particle, float dt) = 0;

protected:
    /**
     * @brief Default constructor (protected to prevent direct instantiation).
     */
    Integrator() = default;

    // --- Prevent Copying/Moving (interfaces typically shouldn't be copied/moved) ---
    Integrator(const Integrator&) = delete;
    Integrator& operator=(const Integrator&) = delete;
    Integrator(Integrator&&) = delete;
    Integrator& operator=(Integrator&&) = delete;
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_INTEGRATOR_H