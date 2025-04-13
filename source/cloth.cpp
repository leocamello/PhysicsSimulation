/**
 * @file cloth.cpp
 * @brief Implements the Cloth class methods.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/cloth.h"
#include "PhysicsSimulation/graphics.h" // Include for Draw()
#include "PhysicsSimulation/particle.h" // Included via cloth.h
#include "PhysicsSimulation/vector.h"   // Included via cloth.h
#include <vector>                       // For std::vector
#include <stdexcept>                    // For std::invalid_argument
#include <numeric>                      // For std::iota (optional for index generation)

//namespace PhysicsSimulation {

Cloth::Cloth() noexcept
    // Default constructor initializes members to default values (0, empty vector, white color)
{}

Cloth::Cloth(float total_mass, float particle_radius,
             int n_u, int n_v,
             const Vector3& p, const Vector3& p_u, const Vector3& p_v,
             const Vector3& color, Particle::Type type)
    : dim_u_(n_u), dim_v_(n_v), color_(color) {

    if (dim_u_ <= 1 || dim_v_ <= 1) {
        // Handle invalid dimensions, maybe throw or default to empty
        dim_u_ = 0;
        dim_v_ = 0;
        // Consider throwing std::invalid_argument("Cloth dimensions must be > 1");
        return;
    }

    const int num_particles = dim_u_ * dim_v_;
    if (num_particles <= 0) {
        return; // Should not happen if dim checks pass, but safety first
    }

    const float mass_per_particle = (num_particles > 0) ? total_mass / static_cast<float>(num_particles) : 0.0f;

    particles_.resize(num_particles); // Allocate space in the vector

    // Calculate displacement vectors per grid step
    Vector3 d_u = (p_u - p) / static_cast<float>(dim_u_ - 1);
    Vector3 d_v = (p_v - p) / static_cast<float>(dim_v_ - 1);

    // Initialize particles using the Particle constructor
    for (int i = 0; i < dim_u_; ++i) {
        for (int j = 0; j < dim_v_; ++j) {
            int index = GetIndex(i, j);
            Vector3 position = p + d_u * static_cast<float>(i) + d_v * static_cast<float>(j);
            // Use placement new or direct assignment if Particle is movable
            particles_[index] = Particle(mass_per_particle, particle_radius, position, {}, color, type);
        }
    }
}

// Destructor is defaulted in the header, std::vector handles memory.

int Cloth::GetIndex(int u, int v) const noexcept {
    // Add bounds checking if necessary, though internal usage should be safe
    // assert(u >= 0 && u < dim_u_ && v >= 0 && v < dim_v_);
    return u * dim_v_ + v; // Assuming row-major or similar layout consistent with initialization
                           // Double-check this matches the original logic's intent
                           // Original seemed to iterate i (u) outer, j (v) inner -> u * nV + j
}

void Cloth::Draw() const {
    if (particles_.empty() || dim_u_ <= 1 || dim_v_ <= 1) {
        return; // Cannot draw an empty or degenerate cloth
    }

    // Prepare vertex coordinates
    std::vector<float> coords;
    coords.reserve(particles_.size() * 3);
    for (const auto& p : particles_) {
        const Vector3& pos = p.position(); // Use getter
        coords.push_back(pos.x);
        coords.push_back(pos.y);
        coords.push_back(pos.z);
    }

    // Prepare indices for two sets of quads (alternating colors)
    std::vector<unsigned int> indices1;
    std::vector<unsigned int> indices2;
    const size_t quads_per_row = dim_v_ - 1;
    const size_t num_quads = (dim_u_ - 1) * quads_per_row;
    indices1.reserve(num_quads * 2); // Reserve approx half (worst case)
    indices2.reserve(num_quads * 2); // Reserve approx half

    for (int i = 0; i < dim_u_ - 1; ++i) {
        for (int j = 0; j < dim_v_ - 1; ++j) {
            unsigned int p00 = GetIndex(i, j);
            unsigned int p01 = GetIndex(i, j + 1);
            unsigned int p10 = GetIndex(i + 1, j);
            unsigned int p11 = GetIndex(i + 1, j + 1);

            // Alternate based on grid position (checkerboard pattern)
            if ((i + j) % 2 == 0) {
                indices1.push_back(p00);
                indices1.push_back(p10); // Changed order for consistent winding? Check original intent.
                indices1.push_back(p11);
                indices1.push_back(p01);
            } else {
                indices2.push_back(p00);
                indices2.push_back(p10); // Changed order for consistent winding? Check original intent.
                indices2.push_back(p11);
                indices2.push_back(p01);
            }
        }
    }

    // Draw the two sets of quads with different colors
    // TODO: Check if Graphics::DrawQuads can take Vector3 color directly
    if (!indices1.empty()) {
        Graphics::DrawQuads(indices1.size(), indices1.data(), coords.data(),
                            color_.x, color_.y, color_.z);
    }
    if (!indices2.empty()) {
        // Use complementary color for the second set
        Graphics::DrawQuads(indices2.size(), indices2.data(), coords.data(),
                            1.0f - color_.x, 1.0f - color_.y, 1.0f - color_.z);
    }
}

// Removed empty Update() method implementation.

//} // namespace PhysicsSimulation