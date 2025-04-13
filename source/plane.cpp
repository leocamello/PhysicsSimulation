/**
 * @file plane.cpp
 * @brief Implements the Plane class methods.
 * @author L. Camello (original), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/plane.h"
#include "PhysicsSimulation/graphics.h" // Include for Draw()
#include "PhysicsSimulation/vector.h"   // Included via plane.h

//namespace PhysicsSimulation {

Plane::Plane() noexcept
    // Use member initializer list with default values defined in the header
{}

Plane::Plane(const Vector3& normal, const Vector3& position, float size,
             const Vector3& color) noexcept
    : normal_(normal), // TODO: Consider normalizing normal here if not guaranteed by caller
      position_(position),
      size_(size),
      color_(color)
{}

// Destructor is defaulted in the header, no implementation needed here.

void Plane::Draw() const {
    // Assuming Graphics::DrawPlane still requires individual float components
    // TODO: Check if Graphics::DrawPlane can take Vector3 directly
    Graphics::DrawPlane(
        position_.x, position_.y, position_.z,
        normal_.x, normal_.y, normal_.z,
        size_,
        color_.x, color_.y, color_.z);
}

// No Update method needed as it was empty.

//} // namespace PhysicsSimulation
