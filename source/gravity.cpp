/**
 * @file gravity.cpp
 * @brief Implements the GravityForceGenerator class methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/gravity.h" // Use new header name
#include "PhysicsSimulation/particle.h"             // Include Particle definition
#include "PhysicsSimulation/vector.h"               // Include Vector3 definition (needed for constructor)

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

// Define default gravity constant if needed elsewhere, or just use literal here
// constexpr Vector3 kDefaultGravity(0.0f, -9.8f, 0.0f);

GravityForceGenerator::GravityForceGenerator(const Vector3& acceleration) noexcept
    : acceleration_(acceleration) {}

GravityForceGenerator::GravityForceGenerator() noexcept
    : acceleration_(0.0f, -9.8f, 0.0f) {} // Default Earth gravity

void GravityForceGenerator::ApplyForce(Particle& particle) {
    // Ensure the particle has finite, positive mass before applying force F = m*a
    // Note: Particle::AddForce already handles kFixed type internally.
    if (particle.mass() <= 0.0f) { // Check for zero or negative mass
        return; // Cannot apply force to objects with zero/negative mass
    }

    // Calculate gravitational force (F = m * g)
    Vector3 gravity_force = acceleration_ * particle.mass();

    // Add the calculated force to the particle's accumulator
    particle.AddForce(gravity_force);
}

void GravityForceGenerator::set_acceleration(const Vector3& acceleration) noexcept {
    acceleration_ = acceleration;
}

const Vector3& GravityForceGenerator::acceleration() const noexcept {
    return acceleration_;
}

// } // namespace PhysicsSimulation