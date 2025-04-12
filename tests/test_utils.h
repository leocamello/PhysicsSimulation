#ifndef PHYSICS_SIMULATION_TEST_UTILS_H
#define PHYSICS_SIMULATION_TEST_UTILS_H

#include <cmath> // For std::abs (or std::fabs)
#include "PhysicsSimulation/vector.h" // For Vector3 definition

// Helper function for comparing floats with a tolerance
// Marked inline to prevent multiple definition errors
inline bool AreFloatsClose(float a, float b, float tolerance = 1e-5f) {
    // Use std::fabs for float absolute value
    return std::fabs(a - b) < tolerance;
}

// Helper function for comparing Vector3 (uses AreFloatsClose)
// Marked inline to prevent multiple definition errors
inline bool AreVectorsClose(const Vector3& v1, const Vector3& v2, float tolerance = 1e-5f) {
    return AreFloatsClose(v1.x, v2.x, tolerance) &&
           AreFloatsClose(v1.y, v2.y, tolerance) &&
           AreFloatsClose(v1.z, v2.z, tolerance);
}

#endif // PHYSICS_SIMULATION_TEST_UTILS_H