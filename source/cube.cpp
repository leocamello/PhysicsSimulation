/**
 * @file cube.cpp
 * @brief Implements the Cube class methods.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/cube.h"
#include "PhysicsSimulation/graphics.h" // Include for Draw()
#include "PhysicsSimulation/particle.h" // Included via cube.h
#include "PhysicsSimulation/vector.h"   // Included via cube.h
#include <array>                        // For std::array used in Draw
#include <vector>                       // For std::vector used in Draw

//namespace PhysicsSimulation {

Cube::Cube() noexcept {
    // Default constructor initializes particles_ using Particle's default constructor.
    // color_ uses its default member initializer.
}

Cube::Cube(const Vector3& center, float size,
           float particle_mass, float particle_radius,
           const Vector3& color, Particle::Type type) noexcept
    : color_(color) {
    // Calculate half-size for easier vertex positioning
    const float half_size = size * 0.5f;
    const float x_min = center.x - half_size;
    const float x_max = center.x + half_size;
    const float y_min = center.y - half_size;
    const float y_max = center.y + half_size;
    const float z_min = center.z - half_size;
    const float z_max = center.z + half_size;

    // Use the Particle constructor to initialize each particle in the array
    particles_[0] = Particle(particle_mass, particle_radius, {x_min, y_max, z_min}, {}, color, type);
    particles_[1] = Particle(particle_mass, particle_radius, {x_max, y_max, z_min}, {}, color, type);
    particles_[2] = Particle(particle_mass, particle_radius, {x_max, y_max, z_max}, {}, color, type);
    particles_[3] = Particle(particle_mass, particle_radius, {x_min, y_max, z_max}, {}, color, type);
    particles_[4] = Particle(particle_mass, particle_radius, {x_min, y_min, z_min}, {}, color, type);
    particles_[5] = Particle(particle_mass, particle_radius, {x_max, y_min, z_min}, {}, color, type);
    particles_[6] = Particle(particle_mass, particle_radius, {x_max, y_min, z_max}, {}, color, type);
    particles_[7] = Particle(particle_mass, particle_radius, {x_min, y_min, z_max}, {}, color, type);
    // Note: Initial velocity is default (zero). Color is passed to particles too.
}

// Destructor is defaulted in the header.

void Cube::Draw() const {
    // Prepare vertex coordinates for Graphics::DrawQuads
    std::vector<float> coords;
    coords.reserve(kNumVertices * 3); // Reserve space for efficiency
    for (const auto& p : particles_) {
        const Vector3& pos = p.position(); // Use getter
        coords.push_back(pos.x);
        coords.push_back(pos.y);
        coords.push_back(pos.z);
    }

    // Define the indices for the 6 faces (quads)
    // Using std::array for compile-time safety and clarity
    static constexpr std::array<unsigned int, kNumFaces * 4> kQuadIndices = {
        0, 3, 2, 1, // Top face
        4, 5, 6, 7, // Bottom face
        0, 1, 5, 4, // Front face
        1, 2, 6, 5, // Right face
        2, 3, 7, 6, // Back face
        0, 4, 7, 3  // Left face
    };

    // Call the graphics function
    // TODO: Check if Graphics::DrawQuads can take Vector3 color directly
    // NOTE: Using const_cast as DrawQuads expects unsigned int* but indices are const.
    // This assumes DrawQuads does not modify the index data.
    Graphics::DrawQuads(
        kQuadIndices.size(), // Total number of indices
        const_cast<unsigned int*>(kQuadIndices.data()), // Pointer to index data
        coords.data(),       // Pointer to coordinate data
        color_.x, color_.y, color_.z); // Use color_ members
}

// Removed empty Update() method implementation.

//} // namespace PhysicsSimulation