/**
 * @file particle.h
 * @brief Defines the Particle class representing a basic physical entity.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_PARTICLE_H
#define PHYSICS_SIMULATION_PARTICLE_H

#include "PhysicsSimulation/vector.h" // Include Vector3 definition

// Forward declarations
// namespace Graphics { class ???; } // Forward declare Graphics if needed for Draw

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

/**
 * @brief Represents a point mass particle in the physics simulation.
 *
 * Stores the particle's physical state (position, velocity, mass, etc.)
 * and accumulates forces acting upon it.
 */
class Particle {
public:
    /** @brief Defines the type/state of the particle (e.g., active or fixed). */
    enum class Type {
        kActive, // Particle moves according to physics
        kFixed   // Particle position is fixed (infinite mass conceptually)
        // TODO: Add other types if needed (e.g., kStatic for immovable objects)
    };

    /**
     * @brief Default constructor. Initializes a particle at the origin with zero mass and velocity.
     */
    Particle() noexcept;

    /**
     * @brief Constructs a particle with specified initial state.
     *
     * @param mass The mass of the particle (should be > 0 for movable objects).
     * @param radius The radius of the particle (for collision/visualization).
     * @param position The initial position vector.
     * @param velocity The initial velocity vector.
     * @param color The color for visualization (default: white).
     * @param type The type of the particle (default: kActive).
     */
    Particle(float mass, float radius,
             const Vector3& position, const Vector3& velocity,
             const Vector3& color = Vector3(1.0f, 1.0f, 1.0f),
             Type type = Type::kActive) noexcept;

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Particle() = default;

    // --- Prevent Copying (for now) ---
    // Copying particles might require careful handling of state.
    // If copying is needed, implement proper copy constructor/assignment.
    Particle(const Particle&) = delete;
    Particle& operator=(const Particle&) = delete;

    // --- Allow Moving ---
    // Moving particles is generally safe and useful for container management.
    Particle(Particle&&) noexcept = default;
    Particle& operator=(Particle&&) noexcept = default;

    /**
     * @brief Adds a force vector to the particle's force accumulator.
     * @param force The force vector to add.
     */
    void AddForce(const Vector3& force) noexcept;

    /**
     * @brief Clears the accumulated forces on the particle (sets to zero).
     * Should be called typically at the beginning of each simulation step.
     */
    void ClearForceAccumulator() noexcept;

    /**
     * @brief Draws the particle visually (implementation depends on Graphics interface).
     * @note Consider moving drawing logic outside the core physics class.
     */
    void Draw() const;

    // --- Accessors (Getters) ---
    float mass() const noexcept { return mass_; }
    float radius() const noexcept { return radius_; }
    const Vector3& position() const noexcept { return position_; }
    const Vector3& velocity() const noexcept { return velocity_; }
    const Vector3& previous_position() const noexcept { return previous_position_; }
    const Vector3& force_accumulator() const noexcept { return force_accumulator_; }
    const Vector3& color() const noexcept { return color_; }
    Type type() const noexcept { return type_; }

    // --- Mutators (Setters) ---
    // Use setters sparingly. Prefer updating state via integration/forces.
    void set_position(const Vector3& position) noexcept { position_ = position; }
    void set_velocity(const Vector3& velocity) noexcept { velocity_ = velocity; }
    void set_previous_position(const Vector3& prev_pos) noexcept { previous_position_ = prev_pos; }
    void set_mass(float mass) noexcept { mass_ = mass; } // Be careful changing mass mid-simulation
    void set_radius(float radius) noexcept { radius_ = radius; }
    void set_color(const Vector3& color) noexcept { color_ = color; }
    void set_type(Type type) noexcept { type_ = type; }


    // --- Friend Declarations (for Integrators) ---
    // Grant specific classes access to private members if necessary for performance
    // or tight coupling (like integrators modifying position/velocity directly).
    // Use this cautiously. Prefer using public methods if possible.
    friend class EulerIntegrator;
    friend class VerletIntegrator;
    // Add other friends if needed (e.g., specific collision handlers)

private:
    // --- Physical Properties ---
    float mass_ = 0.0f;          /**< Mass of the particle. */
    float radius_ = 0.1f;        /**< Radius (for collision/visualization). */

    // --- State Variables ---
    Vector3 position_;           /**< Current position vector p(t). */
    Vector3 velocity_;           /**< Current velocity vector v(t). */
    Vector3 previous_position_;  /**< Position vector at the previous time step p(t-dt). Used by Verlet. */

    // --- Force Accumulation ---
    Vector3 force_accumulator_;  /**< Sum of forces acting on the particle in the current step. */

    // --- Visual/Type Properties ---
    Vector3 color_ = {1.0f, 1.0f, 1.0f}; /**< Color for visualization. */
    Type type_ = Type::kActive;         /**< Particle type (active, fixed, etc.). */

    // Deprecated members (to be removed after confirming they are unused)
    // float _invMass;
    // Vector3 _resultantForce; // Replaced by force_accumulator_
    // Vector3 _currPosition;   // Replaced by position_
    // Vector3 _currVelocity;   // Replaced by velocity_
    // Vector3 _prevPosition;   // Replaced by previous_position_
    // ParticleType _particleType; // Replaced by type_
};

// } // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_PARTICLE_H