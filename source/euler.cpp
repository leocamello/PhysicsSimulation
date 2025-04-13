/**
 * @file euler.cpp
 * @brief Implements the EulerIntegrator class methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/euler.h"
#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition

void EulerIntegrator::Integrate(const Vector3& acceleration, Particle& particle, float dt) {
    // Ensure dt is non-negative; handle potential issues if necessary
    if (dt <= 0.0f) {
        return; // Or handle as an error/assertion
    }

    // Update position: p(t+dt) = p(t) + v(t) * dt
    particle.position_ += particle.velocity_ * dt;

    // Update velocity: v(t+dt) = v(t) + a(t) * dt
    particle.velocity_ += acceleration * dt;

    // Note: This integrator does not update particle.previous_position
}