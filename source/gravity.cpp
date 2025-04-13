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
    // Ensure the particle has finite mass before applying force F = m*a
    // TODO: Update member names once Particle class members are renamed.
    // Using current names (_mass, _resultantForce) as requested.
    if (particle._mass <= 0.0f) { // Check for zero or negative mass
        return; // Cannot apply force to objects with infinite/invalid mass
    }

    // Add gravitational force (F = m * g) to the particle's resultant force
    // particle.resultant_force += acceleration_ * particle.mass; // Target code
    particle._resultantForce += acceleration_ * particle._mass;
}

void GravityForceGenerator::set_acceleration(const Vector3& acceleration) noexcept {
    acceleration_ = acceleration;
}

const Vector3& GravityForceGenerator::acceleration() const noexcept {
    return acceleration_;
}

// } // namespace PhysicsSimulation