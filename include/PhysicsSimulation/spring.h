/**
 * @file spring.h
 * @brief Defines the Spring class representing a damped spring force between two particles.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_SPRING_H // Consistent include guard
#define PHYSICS_SIMULATION_SPRING_H

#include "PhysicsSimulation/vector.h" // Include Vector3 definition

// Forward declarations
class Particle;
// namespace Graphics { class ???; } // Forward declare Graphics if needed for Draw

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Represents a damped spring connecting two particles.
 *
 * Calculates and applies forces to both connected particles based on Hooke's Law
 * and a damping factor proportional to the relative velocity along the spring axis.
 */
class Spring {
public:
    /**
     * @brief Constructor calculating rest length from initial particle positions.
     * @param stiffness The spring constant (k > 0).
     * @param damping The damping coefficient (b >= 0).
     * @param particle_a Pointer to the first connected particle (must not be null).
     * @param particle_b Pointer to the second connected particle (must not be null and different from particle_a).
     * @throws std::invalid_argument if particle pointers are null or the same, or if stiffness/damping are invalid.
     */
    Spring(float stiffness, float damping, Particle* particle_a, Particle* particle_b);

    /**
     * @brief Constructor specifying the rest length explicitly.
     * @param stiffness The spring constant (k > 0).
     * @param damping The damping coefficient (b >= 0).
     * @param particle_a Pointer to the first connected particle (must not be null).
     * @param particle_b Pointer to the second connected particle (must not be null and different from particle_a).
     * @param rest_length The natural length of the spring when no force is applied (l0 >= 0).
     * @throws std::invalid_argument if particle pointers are null or the same, or if stiffness/damping/rest_length are invalid.
     */
    Spring(float stiffness, float damping, Particle* particle_a, Particle* particle_b, float rest_length);

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Spring() = default;

    // --- Prevent Copying/Moving ---
    // Copying doesn't make sense without defining ownership or deep copy semantics.
    // Moving could be implemented if needed, but deleted for simplicity now.
    Spring(const Spring&) = delete;
    Spring& operator=(const Spring&) = delete;
    Spring(Spring&&) = delete;
    Spring& operator=(Spring&&) = delete;

    /**
     * @brief Calculates and applies the spring and damping forces to the connected particles.
     *
     * Adds the calculated force to particle_a's resultant force and the
     * negative of the force to particle_b's resultant force.
     */
    void ApplyForce();

    /**
     * @brief Draws the spring visually (implementation depends on Graphics interface).
     * @note Consider moving drawing logic outside the core physics class.
     */
    void Draw() const;

    // --- Accessors ---
    float stiffness() const noexcept { return stiffness_; }
    float damping() const noexcept { return damping_; }
    float rest_length() const noexcept { return rest_length_; }
    Particle* particle_a() const noexcept { return particle_a_; }
    Particle* particle_b() const noexcept { return particle_b_; }

private:
    float stiffness_;     /**< Spring constant (k). */
    float damping_;       /**< Damping coefficient (b). */
    float rest_length_;   /**< Natural length of the spring (l0). */
    Particle* particle_a_; /**< Pointer to the first connected particle. */
    Particle* particle_b_; /**< Pointer to the second connected particle. */
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_SPRING_H