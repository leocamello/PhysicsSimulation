/**
 * @file particle.cpp
 * @brief Implements the Particle class methods.
 * @author L. Camello (original), L. Nascimento (updated)
 * @date 2025-04-12
 */

#include "PhysicsSimulation/graphics.h" // Assuming graphics.h is namespaced or will be
#include "PhysicsSimulation/particle.h"

// TODO: Consider uncommenting and using this namespace
// namespace PhysicsSimulation {

Particle::Particle() noexcept
{
    // Default member initialization handles setup
}

Particle::~Particle() noexcept
{
    // No resources to release
}

// Documentation is primarily in the header file (.h)
void Particle::Initialize(
        float m,
        float radius,
        float x, float y, float z,
        float r, float g, float b,
        ParticleType type) noexcept
{
    _red = r;
    _green = g;
    _blue = b;
    _mass = m;
    _radius = radius;
    _currPosition.Set(x, y, z); // Use Set method if available
    _currVelocity.Set(0.0f, 0.0f, 0.0f);
    _resultantForce.Set(0.0f, 0.0f, 0.0f);
    _prevPosition = _currPosition; // Initialize previous position
    _particleType = type;
}

// Documentation is primarily in the header file (.h)
void Particle::Initialize(
        float m,
        float radius,
        float px, float py, float pz,
        float vx, float vy, float vz,
        float r, float g, float b,
        ParticleType type) noexcept
{
    _red = r;
    _green = g;
    _blue = b;
    _mass = m;
    _radius = radius;
    _currPosition.Set(px, py, pz);
    _currVelocity.Set(vx, vy, vz);
    _resultantForce.Set(0.0f, 0.0f, 0.0f);
    _prevPosition = _currPosition; // Initialize previous position
    _particleType = type;
}

// Documentation is primarily in the header file (.h)
void Particle::Update() noexcept
{
    // Implementation depends on the chosen integration method (e.g., Verlet, Euler)
    // This function might update _prevPosition, _currPosition, _currVelocity
}

// Documentation is primarily in the header file (.h)
void Particle::DrawPoint()
{
    // Use Vector3 components directly
    float color[3] = {_red, _green, _blue};
    float coord[3] = {_currPosition.x, _currPosition.y, _currPosition.z};

    // Assuming Graphics is a static class or namespace
    Graphics::DrawPointParticles(1, _radius, coord, color);
}

// Documentation is primarily in the header file (.h)
void Particle::DrawSphere()
{
    // Use Vector3 components directly
    float color[3] = {_red, _green, _blue};
    float coord[3] = {_currPosition.x, _currPosition.y, _currPosition.z};

    // Assuming Graphics is a static class or namespace
    Graphics::DrawSphereParticles(1, _radius, coord, color);
}

// Documentation is primarily in the header file (.h)
void Particle::ResetForces() noexcept
{
    _resultantForce.Set(0.0f, 0.0f, 0.0f); // Use Set method
}

// } // namespace PhysicsSimulation

