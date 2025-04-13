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
#include <cmath>     // For std::fabs

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

    const Vector3 direction = particle_a_->_currPosition - particle_b_->_currPosition;
    rest_length_ = direction.Length();
     if (rest_length_ < 1e-6f) {
         rest_length_ = 0.0f;
     }
}

Spring::Spring(float stiffness, float damping, Particle* particle_a, Particle* particle_b, float rest_length)
    : stiffness_(stiffness), damping_(damping), rest_length_(rest_length),
      particle_a_(particle_a), particle_b_(particle_b) {

    ValidateSpringParameters(stiffness_, damping_, particle_a_, particle_b_, rest_length_);
}

void Spring::ApplyForce() {
    if (!particle_a_ || !particle_b_) {
        return;
    }

    Vector3 direction = particle_a_->_currPosition - particle_b_->_currPosition;
    float current_length = direction.Length();

    if (current_length < 1e-6f) {
        return;
    }

    Vector3 unit_direction = direction / current_length;

    Vector3 relative_velocity = particle_a_->_currVelocity - particle_b_->_currVelocity;
    float velocity_along_direction = Dot(relative_velocity, unit_direction);

    float spring_magnitude = -stiffness_ * (current_length - rest_length_);
    float damping_magnitude = -damping_ * velocity_along_direction;

    float total_magnitude = spring_magnitude + damping_magnitude;
    Vector3 total_force = unit_direction * total_magnitude;

    particle_a_->_resultantForce += total_force;
    particle_b_->_resultantForce -= total_force;
}

void Spring::Draw() const {
     if (!particle_a_ || !particle_b_) {
        return;
    }

    float coord1[3] = {
        particle_a_->_currPosition.x,
        particle_a_->_currPosition.y,
        particle_a_->_currPosition.z};
    float coord2[3] = {
        particle_b_->_currPosition.x,
        particle_b_->_currPosition.y,
        particle_b_->_currPosition.z};

    float current_length = (particle_a_->_currPosition - particle_b_->_currPosition).Length();

    Graphics::DrawSpring(current_length, rest_length_, coord1, coord2);
}