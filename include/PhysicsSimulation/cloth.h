/**
 * @file cloth.h
 * @brief Defines the Cloth class representing a grid of interconnected particles.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_CLOTH_H
#define PHYSICS_SIMULATION_CLOTH_H

#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition
#include <vector>                       // Include for std::vector

//namespace PhysicsSimulation {

/**
 * @brief Represents a rectangular piece of cloth simulated as a grid of particles.
 *
 * Manages the particles forming the cloth grid. Springs or constraints
 * connecting the particles need to be added externally by the simulation setup.
 */
class Cloth {
public:
    /**
     * @brief Default constructor. Creates an empty cloth.
     */
    Cloth() noexcept;

    /**
     * @brief Constructs a cloth grid with specified dimensions and properties.
     *
     * Creates a grid of n_u x n_v particles. The grid is defined by a starting
     * point 'p' and two vectors 'p_u' and 'p_v' defining the grid's extent
     * and orientation in space.
     *
     * @param total_mass The total mass of the cloth (distributed evenly among particles).
     * @param particle_radius The radius to assign to each particle.
     * @param n_u Number of particles along the 'u' dimension.
     * @param n_v Number of particles along the 'v' dimension.
     * @param p The position of the particle at index (0, 0).
     * @param p_u The position of the particle at index (n_u-1, 0).
     * @param p_v The position of the particle at index (0, n_v-1).
     * @param color The color for visualization (default: white).
     * @param type The type for all particles (default: kActive).
     */
    Cloth(float total_mass, float particle_radius,
          int n_u, int n_v,
          const Vector3& p, const Vector3& p_u, const Vector3& p_v,
          const Vector3& color = Vector3(1.0f, 1.0f, 1.0f),
          Particle::Type type = Particle::Type::kActive);

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Cloth() = default;

    // --- Prevent Copying ---
    Cloth(const Cloth&) = delete;
    Cloth& operator=(const Cloth&) = delete;

    // --- Allow Moving ---
    Cloth(Cloth&&) noexcept = default;
    Cloth& operator=(Cloth&&) noexcept = default;

    /**
     * @brief Draws the cloth visually as a grid of quads.
     * @note Implementation depends on the Graphics interface. Uses alternating colors.
     */
    void Draw() const;

    // --- Accessors (Getters) ---
    int dim_u() const noexcept { return dim_u_; }
    int dim_v() const noexcept { return dim_v_; }
    const std::vector<Particle>& particles() const noexcept { return particles_; }
    std::vector<Particle>& particles() noexcept { return particles_; } // Non-const version
    const Vector3& color() const noexcept { return color_; }
    // Add getters for mass/radius if needed, though they are per-particle

    // --- Mutators (Setters) ---
    void set_color(const Vector3& color) noexcept { color_ = color; }
    // Add setters for particle properties if needed

    /**
     * @brief Helper to get the 1D index from 2D grid coordinates.
     * @param u Index along the U dimension.
     * @param v Index along the V dimension.
     * @return The 1D index in the particles_ vector.
     */
    int GetIndex(int u, int v) const noexcept;

private:
    int dim_u_ = 0;                         /**< Number of particles along the U dimension. */
    int dim_v_ = 0;                         /**< Number of particles along the V dimension. */
    std::vector<Particle> particles_;       /**< Vector storing all particles. */
    Vector3 color_ = {1.0f, 1.0f, 1.0f};    /**< Base color for visualization. */
    // Individual particle mass/radius stored within Particle objects.
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_CLOTH_H