/**
 * @file spring.cpp
 * @brief Implements the Spring class methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/spring.h"
#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition
#include "PhysicsSimulation/graphics.h" // Include for Draw() - Consider alternatives
#include <stdexcept> // For std::invalid_argument
#include <cmath>     // For std::fabs, std::clamp
#include <algorithm> // For std::clamp

// Helper validation function (optional, can be inline in constructors)
namespace {
void ValidateSpringParameters(float stiffness, float damping, Particle* p_a, Particle* p_b, float rest_length = 0.0f) {
    if (!p_a || !p_b) {
        throw std::invalid_argument("Spring particle pointers cannot be null.");
    }
    if (p_a == p_b) {
        throw std::invalid_argument("Spring particles must be different.");
    }
    if (stiffness <= 0.0f) {
        throw std::invalid_argument("Spring stiffness must be positive.");
    }
    if (damping < 0.0f) {
        throw std::invalid_argument("Spring damping cannot be negative.");
    }
     if (rest_length < 0.0f) {
        throw std::invalid_argument("Spring rest length cannot be negative.");
    }
}
} // namespace

Spring::Spring(float stiffness, float damping, Particle* particle_a, Particle* particle_b)
    : stiffness_(stiffness), damping_(damping), particle_a_(particle_a), particle_b_(particle_b) {

    ValidateSpringParameters(stiffness_, damping_, particle_a_, particle_b_);

    // Use getter methods for particle positions
    const Vector3 direction = particle_a_->position() - particle_b_->position();
    rest_length_ = direction.Length();
     if (rest_length_ < 1e-6f) { // Handle case where particles start at the same position
         rest_length_ = 0.0f;
     }
}

Spring::Spring(float stiffness, float damping, Particle* particle_a, Particle* particle_b, float rest_length)
    : stiffness_(stiffness), damping_(damping), rest_length_(rest_length),
      particle_a_(particle_a), particle_b_(particle_b) {

    ValidateSpringParameters(stiffness_, damping_, particle_a_, particle_b_, rest_length_);
}

void Spring::ApplyForce() {
    // Ensure particles are valid (already checked in constructor, but belt-and-suspenders)
    if (!particle_a_ || !particle_b_) {
        return;
    }

    // Use getter methods for particle state
    Vector3 direction = particle_a_->position() - particle_b_->position();
    float current_length = direction.Length();

    // Avoid division by zero or issues if particles are coincident
    if (current_length < 1e-6f) { // Use a small epsilon
        return; // No force can be applied if length is effectively zero
    }

    // Normalize the direction vector
    Vector3 unit_direction = direction / current_length; // Normalize (length is non-zero here)

    // Calculate relative velocity along the spring axis
    Vector3 relative_velocity = particle_a_->velocity() - particle_b_->velocity();
    float velocity_along_direction = Dot(relative_velocity, unit_direction);

    // Calculate spring force (Hooke's Law: F_s = -k * (L - L0) * unit_direction)
    float spring_magnitude = -stiffness_ * (current_length - rest_length_);

    // Calculate damping force (F_d = -b * v_rel_along_axis * unit_direction)
    float damping_magnitude = -damping_ * velocity_along_direction;

    // Calculate total force magnitude
    float total_magnitude = spring_magnitude + damping_magnitude;
    Vector3 total_force = unit_direction * total_magnitude;

    // Apply force to particles using AddForce method
    particle_a_->AddForce(total_force);
    particle_b_->AddForce(-total_force); // Apply equal and opposite force
}

void Spring::Draw() const {
     if (!particle_a_ || !particle_b_) {
        return;
    }

    // Use getter methods for particle positions
    const Vector3 pos_a = particle_a_->position();
    const Vector3 pos_b = particle_b_->position();

    // TODO: Check if Graphics::DrawSpring can take Vector3 directly
    float coord1[3] = {pos_a.x, pos_a.y, pos_a.z};
    float coord2[3] = {pos_b.x, pos_b.y, pos_b.z};

    // Calculate current length for drawing
    float current_length = (pos_a - pos_b).Length();

    Graphics::DrawSpring(current_length, rest_length_, coord1, coord2);
}