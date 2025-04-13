/**
 * @file cube.h
 * @brief Defines the Cube class representing a cube composed of particles.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_CUBE_H
#define PHYSICS_SIMULATION_CUBE_H

#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition
#include <array>                        // Include for std::array

//namespace PhysicsSimulation {

/**
 * @brief Represents a cube shape composed of 8 particles at its vertices.
 *
 * This class manages the particles forming the cube's structure.
 * Note: It doesn't automatically create springs between particles;
 * that needs to be handled externally by the simulation setup.
 */
class Cube {
public:
    /** @brief Number of vertices in a cube. */
    static constexpr size_t kNumVertices = 8;
    /** @brief Number of faces in a cube. */
    static constexpr size_t kNumFaces = 6;

    /**
     * @brief Default constructor. Creates a degenerate cube at the origin.
     */
    Cube() noexcept;

    /**
     * @brief Constructs a cube centered at a position with a given size.
     *
     * @param center The center position of the cube.
     * @param size The full side length of the cube.
     * @param particle_mass The mass to assign to each vertex particle (total mass = 8 * particle_mass).
     * @param particle_radius The radius to assign to each vertex particle.
     * @param color The color for visualization (default: white).
     * @param type The type for all particles (default: kActive).
     */
    Cube(const Vector3& center, float size,
         float particle_mass, float particle_radius,
         const Vector3& color = Vector3(1.0f, 1.0f, 1.0f),
         Particle::Type type = Particle::Type::kActive) noexcept;

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Cube() = default;

    // --- Prevent Copying ---
    Cube(const Cube&) = delete;
    Cube& operator=(const Cube&) = delete;

    // --- Allow Moving ---
    Cube(Cube&&) noexcept = default;
    Cube& operator=(Cube&&) noexcept = default;

    /**
     * @brief Draws the cube visually by drawing quads connecting its particles.
     * @note Implementation depends on the Graphics interface.
     */
    void Draw() const;

    // --- Accessors (Getters) ---
    const std::array<Particle, kNumVertices>& particles() const noexcept { return particles_; }
    std::array<Particle, kNumVertices>& particles() noexcept { return particles_; } // Non-const version
    const Vector3& color() const noexcept { return color_; }
    // Add getters for mass/radius if needed, though they are per-particle

    // --- Mutators (Setters) ---
    void set_color(const Vector3& color) noexcept { color_ = color; }
    // Add setters for particle properties if needed (e.g., set_particle_type)

private:
    std::array<Particle, kNumVertices> particles_; /**< Array of particles at the vertices. */
    Vector3 color_ = {1.0f, 1.0f, 1.0f};          /**< Color for visualization. */
    // Store mass/radius per particle, no need for separate members here if uniform.
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_CUBE_H