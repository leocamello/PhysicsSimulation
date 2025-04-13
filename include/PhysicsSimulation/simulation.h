/**
 * @file simulation.h
 * @brief Defines the Simulation class, which manages the overall physics simulation state and loop.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_SIMULATION_H
#define PHYSICS_SIMULATION_SIMULATION_H

#include "PhysicsSimulation/cloth.h"
#include "PhysicsSimulation/constraint.h"
#include "PhysicsSimulation/cube.h"
#include "PhysicsSimulation/forcegenerator.h"
#include "PhysicsSimulation/integrator.h"
#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/particlegenerator.h"
#include "PhysicsSimulation/plane.h"
#include "PhysicsSimulation/spring.h"
#include "PhysicsSimulation/vector.h"

#include <vector>
#include <memory> // For std::unique_ptr

//namespace PhysicsSimulation {

/**
 * @brief Manages the collection of physical objects, constraints, forces,
 *        and the main simulation loop.
 */
class Simulation {
public:
    /**
     * @brief Default constructor. Initializes an empty simulation.
     */
    Simulation();

    /**
     * @brief Default virtual destructor. Handles cleanup via smart pointers.
     */
    virtual ~Simulation() = default;

    // --- Prevent Copying ---
    Simulation(const Simulation&) = delete;
    Simulation& operator=(const Simulation&) = delete;

    // --- Allow Moving (if needed, default is okay for now) ---
    Simulation(Simulation&&) noexcept = default;
    Simulation& operator=(Simulation&&) noexcept = default;

    // --- Object Addition Methods ---
    // Note: These methods now take ownership via std::unique_ptr

    /** @brief Adds a plane to the simulation, taking ownership. */
    void AddPlane(std::unique_ptr<Plane> plane);
    /** @brief Adds a standalone particle to the simulation, taking ownership. */
    void AddParticle(std::unique_ptr<Particle> particle);
    /** @brief Adds a force generator to the simulation, taking ownership. */
    void AddForceGenerator(std::unique_ptr<ForceGenerator> force_generator);
    /** @brief Adds a particle generator to the simulation, taking ownership. */
    void AddParticleGenerator(std::unique_ptr<ParticleGenerator> particle_generator);
    /** @brief Adds a cube to the simulation, taking ownership and adding its particles. */
    void AddCube(std::unique_ptr<Cube> cube);
    /** @brief Adds a cloth object to the simulation, taking ownership and adding its particles/constraints/springs. */
    void AddCloth(std::unique_ptr<Cloth> cloth);

    // --- Simulation Loop ---
    /**
     * @brief Executes one step of the simulation.
     * @param dt The time step duration (delta time).
     */
    void Update(float dt);

    /**
     * @brief Draws all objects in the simulation.
     */
    void Draw();

    // --- Configuration ---
    /** @brief Sets the integrator used by the simulation, taking ownership. */
    void set_integrator(std::unique_ptr<Integrator> integrator) { integrator_ = std::move(integrator); }
    /** @brief Sets the global dissipative coefficient for collisions. */
    void set_dissipative_coefficient(float dissipative) { dissipative_coefficient_ = dissipative; }
    /** @brief Gets the global dissipative coefficient. */
    float dissipative_coefficient() const { return dissipative_coefficient_; }

private:
    // --- Simulation Steps ---
    void UpdateSprings();
    void UpdateConstraints();
    void UpdateParticles(float dt); // Pass dt down
    void ApplyForces();
    void IntegrateParticles(float dt);
    void HandleCollisions();
    void ClearParticleForces();

    // --- Drawing Steps ---
    void DrawPlanes() const;
    void DrawSprings() const;
    void DrawParticles() const;
    // void DrawConstraints() const; // Optional: if constraints have a visual representation

    // --- Helper Methods ---
    /** @brief Adds a constraint (used internally by AddCloth, etc.). Does not take ownership of particles. */
    void AddConstraint(float length, Particle* particle_a, Particle* particle_b);
    /** @brief Adds a spring (used internally by AddCloth, etc.). Does not take ownership of particles. */
    void AddSpring(float stiffness, float damping, Particle* particle_a, Particle* particle_b);

    // --- Member Variables ---
    // Using std::vector for dynamic arrays and std::unique_ptr for ownership.
    // Raw pointers are used for non-owning references (e.g., particles list).

    std::vector<std::unique_ptr<Plane>> planes_;
    std::vector<std::unique_ptr<Spring>> springs_;
    std::vector<std::unique_ptr<Constraint>> constraints_;
    std::vector<std::unique_ptr<ForceGenerator>> force_generators_;

    // Store owned objects that contain particles
    std::vector<std::unique_ptr<Particle>> owned_particles_; // For standalone particles added via AddParticle
    std::vector<std::unique_ptr<Cube>> cubes_;
    std::vector<std::unique_ptr<Cloth>> cloths_;
    std::vector<std::unique_ptr<ParticleGenerator>> particle_generators_;

    // Non-owning list of all active particles for processing
    std::vector<Particle*> particles_; // Raw pointers to particles owned by others (Cube, Cloth, Generator, owned_particles_)

    std::unique_ptr<Integrator> integrator_;
    float dissipative_coefficient_ = 0.5f;

    // Removed counter members (_currPlane, etc.) - use vector.size() instead.
    // Removed _acceleration member - calculated per-particle in UpdateParticles.
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_SIMULATION_H