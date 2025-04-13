/**
 * @file constraint.cpp
 * @brief Implements the Constraint class methods.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/constraint.h"
#include "PhysicsSimulation/particle.h" // Included via constraint.h
#include "PhysicsSimulation/vector.h"   // Included via constraint.h
#include <cmath>     // For std::fabs
#include <stdexcept> // For std::invalid_argument

//namespace PhysicsSimulation {

Constraint::Constraint(float length, Particle* particle_a, Particle* particle_b)
    : length_(length), particle_a_(particle_a), particle_b_(particle_b) {
    if (!particle_a_ || !particle_b_) {
        throw std::invalid_argument("Constraint particle pointers cannot be null.");
    }
    if (particle_a_ == particle_b_) {
        throw std::invalid_argument("Constraint particles must be different.");
    }
    if (length_ < 0.0f) {
        throw std::invalid_argument("Constraint length cannot be negative.");
    }
}

// Destructor is defaulted in the header.

void Constraint::SatisfyConstraint() {
    // Ensure particles are still valid
    if (!particle_a_ || !particle_b_) {
        return;
    }

    // Get current positions using accessors
    const Vector3& pos_a = particle_a_->position();
    const Vector3& pos_b = particle_b_->position();

    // Calculate vector between particles and current length
    Vector3 delta = pos_b - pos_a;
    float current_length = delta.Length();

    // Avoid division by zero or issues if particles are coincident
    if (current_length < 1e-6f) { // Use a small epsilon
        // Cannot determine direction if coincident.
        return;
    }

    // Calculate the difference from the target length
    float diff = current_length - length_;

    // Calculate the total correction vector needed
    // (delta / current_length) is the normalized direction
    Vector3 correction_vector = delta * (diff / current_length);

    // Determine movement weights based on particle types
    float weight_a = 0.0f;
    float weight_b = 0.0f;
    const bool fixed_a = (particle_a_->type() == Particle::Type::kFixed);
    const bool fixed_b = (particle_b_->type() == Particle::Type::kFixed);

    if (!fixed_a && !fixed_b) {
        // Both movable: distribute correction equally (simple approach)
        // TODO: Distribute based on inverse mass for more physical accuracy.
        weight_a = 0.5f;
        weight_b = 0.5f;
    } else if (fixed_a && !fixed_b) {
        // A fixed, B movable: B gets full correction
        weight_a = 0.0f;
        weight_b = 1.0f;
    } else if (!fixed_a && fixed_b) {
        // A movable, B fixed: A gets full correction
        weight_a = 1.0f;
        weight_b = 0.0f;
    }
    // else: Both fixed - do nothing (weights remain 0.0)

    // Apply corrections using setters, respecting weights
    if (weight_a > 0.0f) {
        particle_a_->set_position(pos_a + correction_vector * weight_a);
    }
    if (weight_b > 0.0f) {
        particle_b_->set_position(pos_b - correction_vector * weight_b);
    }
}

// } // namespace PhysicsSimulation