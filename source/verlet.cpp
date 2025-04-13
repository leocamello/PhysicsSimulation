/**
 * @file verlet.cpp
 * @brief Implements the VerletIntegrator class methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/verlet.h"
#include "PhysicsSimulation/particle.h" // Include Particle definition
#include "PhysicsSimulation/vector.h"   // Include Vector3 definition
#include <algorithm> // For std::clamp (or manual clamp)
#include <cmath>     // For std::fabs

VerletIntegrator::VerletIntegrator(float drag) noexcept {
    // Clamp initial drag value to a reasonable range [0, 1]
    drag_ = std::clamp(drag, 0.0f, 1.0f);
}

void VerletIntegrator::Integrate(const Vector3& acceleration, Particle& particle, float dt) {
    // Ensure dt is positive; handle potential issues if necessary
    if (dt <= 1e-9f) {
        return;
    }

    // Store current position before calculating the new one
    const Vector3 temp_position = particle.position_;

    // Calculate displacement based on previous step: (p(t) - p(t-dt))
    const Vector3 displacement = particle.position_ - particle.previous_position_;

    // Calculate scaled acceleration term: a(t) * dt * dt
    const Vector3 scaled_acceleration = acceleration * (dt * dt);

    // Calculate next position using Verlet formula with drag:
    particle.position_ = particle.position_+ displacement * (1.0f - drag_) + scaled_acceleration;

    // Update previous position for the next step
    particle.previous_position_ = temp_position;
}

void VerletIntegrator::set_drag(float drag) noexcept {
    // Clamp drag value to a reasonable range [0, 1]
    drag_ = std::clamp(drag, 0.0f, 1.0f);
}

float VerletIntegrator::drag() const noexcept {
    return drag_;
}