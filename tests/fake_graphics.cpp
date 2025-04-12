// filepath: /home/lhnascimento/Projects/PhysicsSimulation/tests/fake_graphics.cpp
/**
 * @file fake_graphics.cpp
 * @brief Fake implementation of Graphics functions needed for linking tests.
 * @author GitHub Copilot
 * @date 2025-04-12
 */

// Define a minimal Graphics structure or namespace to match what particle.cpp expects.
// Adjust this if your actual Graphics class is structured differently.
namespace Graphics {

    // Provide dummy implementations for the functions called by Particle
    void DrawPointParticles(int count, float radius, float* coords, float* colors) {
        // Do nothing, or maybe log that this was called if needed for debugging tests.
        // This function just needs to exist to link successfully.
        (void)count; // Suppress unused parameter warnings
        (void)radius;
        (void)coords;
        (void)colors;
    }

    void DrawSphereParticles(int count, float radius, float* coords, float* colors) {
        // Do nothing.
        (void)count; // Suppress unused parameter warnings
        (void)radius;
        (void)coords;
        (void)colors;
    }

    // Add other Graphics functions here if Particle calls them directly or indirectly
    // and causes linker errors.

} // namespace Graphics