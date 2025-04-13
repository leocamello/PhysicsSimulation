/**
 * @file forcegenerator.h
 * @brief Defines the abstract base class for force generators.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_FORCE_GENERATOR_H // Consistent include guard
#define PHYSICS_SIMULATION_FORCE_GENERATOR_H

// Forward declaration to minimize header dependencies
class Particle;

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Abstract base class defining the interface for force generators.
 *
 * Derived classes implement specific force calculations (e.g., gravity, springs)
 * and apply them to particles.
 */
class ForceGenerator {
public:
    /**
     * @brief Virtual destructor. Essential for base classes with virtual functions.
     */
    virtual ~ForceGenerator() = default;

    /**
     * @brief Applies the force calculated by this generator to a given particle.
     *
     * Pure virtual function that must be implemented by derived classes.
     * The implementation should typically add its force contribution to the
     * particle's resultant force.
     *
     * @param particle The particle to apply the force to.
     */
    virtual void ApplyForce(Particle& particle) = 0;

protected:
    /**
     * @brief Default constructor (protected to prevent direct instantiation).
     */
    ForceGenerator() = default;

    // --- Prevent Copying/Moving (interfaces typically shouldn't be copied/moved) ---
    ForceGenerator(const ForceGenerator&) = delete;
    ForceGenerator& operator=(const ForceGenerator&) = delete;
    ForceGenerator(ForceGenerator&&) = delete;
    ForceGenerator& operator=(ForceGenerator&&) = delete;
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_FORCE_GENERATOR_H