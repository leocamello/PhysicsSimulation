/**
 * @file medium.cpp
 * @brief Implements the Medium class methods.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/medium.h"
#include "PhysicsSimulation/particle.h" // Included via medium.h
#include "PhysicsSimulation/vector.h"   // Included via medium.h
#include <stdexcept> // For std::invalid_argument

//namespace PhysicsSimulation {

Medium::Medium(float drag_coefficient)
    : drag_coefficient_(drag_coefficient) {
    if (drag_coefficient_ < 0.0f) {
        throw std::invalid_argument("Medium drag coefficient cannot be negative.");
    }
}

// Destructor is defaulted in the header.

void Medium::ApplyForce(Particle& particle) {
    // Check if particle is fixed or has non-positive mass (drag affects velocity, not mass directly, but good practice)
    // Note: Particle::AddForce already handles kFixed type internally.
    // if (particle.type() == Particle::Type::kFixed) {
    //     return;
    // }

    // Calculate drag force: F_drag = -k * v
    Vector3 drag_force = particle.velocity() * -drag_coefficient_;

    // Add the calculated force to the particle's accumulator
    particle.AddForce(drag_force);
}

void Medium::set_drag_coefficient(float drag_coefficient) {
     if (drag_coefficient < 0.0f) {
        throw std::invalid_argument("Medium drag coefficient cannot be negative.");
    }
    drag_coefficient_ = drag_coefficient;
}

//} // namespace PhysicsSimulation