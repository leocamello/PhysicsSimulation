/**
 * @file particle.h
 * @brief Defines the Particle class representing a point mass in the simulation.
 * @author L. Camello (original), L. Nascimento (updated)
 * @date 2025-04-12
 */

#ifndef PHYSICS_SIMULATION_PARTICLE_H // Renamed include guard for consistency
#define PHYSICS_SIMULATION_PARTICLE_H

#include "vector.h"

// TODO: Consider uncommenting and using this namespace
// namespace PhysicsSimulation {

/**
 * @brief Represents a particle (point mass) in the physics simulation.
 *
 * Stores physical properties like mass, radius, position, velocity,
 * and resultant force. Also handles basic drawing and state updates.
 */
class Particle
{
public:
    /**
     * @brief Defines the type of particle, affecting its behavior in the simulation.
     */
    enum ParticleType
    {
        PASSIVE, /**< Particle is affected by forces but does not exert forces (or has fixed behavior). */
        ACTIVE   /**< Particle actively participates in interactions and force calculations. */
    };

    /** @brief Default constructor. */
    Particle() noexcept; // Added noexcept

    /** @brief Destructor. */
    ~Particle() noexcept; // Added noexcept

    // --- Physical Properties ---
    /** @brief Mass of the particle. */
    float _mass = 1.0f; // Provide default value
    /** @brief Radius of the particle (for collision detection and drawing). */
    float _radius = 0.1f; // Provide default value
    /** @brief Current position vector of the particle. */
    Vector3 _currPosition;
    /** @brief Position vector of the particle in the previous time step. */
    Vector3 _prevPosition;
    /** @brief Current velocity vector of the particle. */
    Vector3 _currVelocity;
    /** @brief Sum of all forces acting on the particle in the current time step. */
    Vector3 _resultantForce;

    // --- Visual Properties ---
    /** @brief Red color component (0.0 to 1.0). */
    float _red = 1.0f; // Provide default value
    /** @brief Green color component (0.0 to 1.0). */
    float _green = 1.0f; // Provide default value
    /** @brief Blue color component (0.0 to 1.0). */
    float _blue = 1.0f; // Provide default value

    // --- Simulation Properties ---
    /** @brief Type of the particle (ACTIVE or PASSIVE). */
    ParticleType _particleType = ACTIVE; // Provide default value

    /**
     * @brief Initializes the particle's state with an initial position and zero velocity.
     * @param m Mass.
     * @param radius Radius.
     * @param x Initial x-coordinate.
     * @param y Initial y-coordinate.
     * @param z Initial z-coordinate.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param type Particle type (ACTIVE or PASSIVE).
     */
    void Initialize(
        float m,
        float radius,
        float x, float y, float z,
        float r, float g, float b,
        ParticleType type) noexcept; // Added noexcept

    /**
     * @brief Initializes the particle's state with an initial position and velocity.
     * @param m Mass.
     * @param radius Radius.
     * @param px Initial x-coordinate.
     * @param py Initial y-coordinate.
     * @param pz Initial z-coordinate.
     * @param vx Initial x-velocity.
     * @param vy Initial y-velocity.
     * @param vz Initial z-velocity.
     * @param r Red color component.
     * @param g Green color component.
     * @param b Blue color component.
     * @param type Particle type (ACTIVE or PASSIVE).
     */
    void Initialize(
        float m,
        float radius,
        float px, float py, float pz,
        float vx, float vy, float vz,
        float r, float g, float b,
        ParticleType type) noexcept; // Added noexcept

    /**
     * @brief Updates the particle's state (currently empty, intended for future integration steps).
     * @note This method is expected to be implemented by integration schemes.
     */
    void Update() noexcept; // Added noexcept

    /**
     * @brief Draws the particle as a point using the Graphics interface.
     */
    void DrawPoint(); // Drawing might interact with external libs, avoid noexcept

    /**
     * @brief Draws the particle as a sphere using the Graphics interface.
     */
    void DrawSphere(); // Drawing might interact with external libs, avoid noexcept

    /**
     * @brief Resets the resultant force acting on the particle to zero.
     * Typically called at the beginning of each simulation step before calculating new forces.
     */
    void ResetForces() noexcept; // Added noexcept
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_PARTICLE_H