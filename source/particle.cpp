/**
 * @file particle.cpp
 * @brief Implements the Particle class methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/particle.h"
#include "PhysicsSimulation/graphics.h" // Include for Draw() - Consider alternatives
#include "PhysicsSimulation/vector.h"   // Included via particle.h, but good practice

// namespace PhysicsSimulation { // TODO: Add namespace if used elsewhere

Particle::Particle() noexcept
    : mass_(0.0f),
      radius_(0.1f),
      position_(0.0f, 0.0f, 0.0f),
      velocity_(0.0f, 0.0f, 0.0f),
      previous_position_(0.0f, 0.0f, 0.0f),
      force_accumulator_(0.0f, 0.0f, 0.0f),
      color_(1.0f, 1.0f, 1.0f),
      type_(Type::kActive)
{}

Particle::Particle(float mass, float radius,
                   const Vector3& position, const Vector3& velocity,
                   const Vector3& color, Type type) noexcept
    : mass_(mass),
      radius_(radius),
      position_(position),
      velocity_(velocity),
      previous_position_(position),
      force_accumulator_(0.0f, 0.0f, 0.0f),
      color_(color),
      type_(type)
{}

void Particle::AddForce(const Vector3& force) noexcept {
    if (type_ != Type::kFixed) {
        force_accumulator_ += force;
    }
}

void Particle::ClearForceAccumulator() noexcept {
    force_accumulator_.Set(0.0f, 0.0f, 0.0f);
}

void Particle::Draw() const {
    float pos_arr[3] = {position_.x, position_.y, position_.z};
    float col_arr[3] = {color_.x, color_.y, color_.z};

    bool use_spheres = true;

    if (use_spheres) {
        Graphics::DrawSphereParticles(1, radius_, pos_arr, col_arr);
    } else {
        Graphics::DrawPointParticles(1, radius_, pos_arr, col_arr);
    }
}

// } // namespace PhysicsSimulation

