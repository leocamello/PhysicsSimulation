/**
 * @file plane.h
 * @brief Defines the Plane class representing an infinite mathematical plane for collision and visualization.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#ifndef PHYSICS_SIMULATION_PLANE_H
#define PHYSICS_SIMULATION_PLANE_H

#include "PhysicsSimulation/vector.h" // Include Vector3 definition

// Forward declarations
// namespace Graphics { class ???; } // Forward declare Graphics if needed for Draw

//namespace PhysicsSimulation {

/**
 * @brief Represents an infinite mathematical plane defined by a normal and a point.
 *
 * Used primarily for collision detection and visualization (often drawn as a finite quad).
 */
class Plane {
public:
    /**
     * @brief Default constructor. Initializes a horizontal plane at the origin.
     */
    Plane() noexcept;

    /**
     * @brief Constructs a plane with specified properties.
     *
     * @param normal The normal vector of the plane (should be normalized).
     * @param position A point lying on the plane (often the origin projected onto the plane).
     * @param size A hint for drawing the visual representation (e.g., side length of a quad).
     * @param color The color for visualization (default: gray).
     */
    Plane(const Vector3& normal, const Vector3& position, float size = 10.0f,
          const Vector3& color = Vector3(0.5f, 0.5f, 0.5f)) noexcept;

    /**
     * @brief Default virtual destructor.
     */
    virtual ~Plane() = default;

    // --- Prevent Copying (for now) ---
    Plane(const Plane&) = delete;
    Plane& operator=(const Plane&) = delete;

    // --- Allow Moving ---
    Plane(Plane&&) noexcept = default;
    Plane& operator=(Plane&&) noexcept = default;

    /**
     * @brief Draws the plane visually (implementation depends on Graphics interface).
     * @note Typically draws a finite representation (e.g., a large quad).
     */
    void Draw() const;

    // --- Accessors (Getters) ---
    const Vector3& normal() const noexcept { return normal_; }
    const Vector3& position() const noexcept { return position_; } // A point on the plane
    float size() const noexcept { return size_; } // Hint for drawing size
    const Vector3& color() const noexcept { return color_; }

    // --- Mutators (Setters) ---
    // Add setters if the plane's properties need to change after creation
    void set_normal(const Vector3& normal) noexcept { normal_ = normal; /* TODO: Consider normalizing */ }
    void set_position(const Vector3& position) noexcept { position_ = position; }
    void set_size(float size) noexcept { size_ = size; }
    void set_color(const Vector3& color) noexcept { color_ = color; }

private:
    Vector3 normal_ = {0.0f, 1.0f, 0.0f}; /**< Normal vector of the plane. */
    Vector3 position_ = {0.0f, 0.0f, 0.0f}; /**< A point on the plane. */
    float size_ = 10.0f;                  /**< Size hint for drawing. */
    Vector3 color_ = {0.5f, 0.5f, 0.5f};   /**< Color for visualization. */
};

//} // namespace PhysicsSimulation

#endif // PHYSICS_SIMULATION_PLANE_H