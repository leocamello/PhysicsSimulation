/**
 * @file simulation.cpp
 * @brief Implements the Simulation class methods.
 * @author L. Camello (original), L. Nascimento (updated), GitHub Copilot (refactored)
 * @date 2025-04-13
 */

#include "PhysicsSimulation/simulation.h"
#include "PhysicsSimulation/graphics.h" // For drawing calls
#include "PhysicsSimulation/euler.h"    // Default integrator example
#include "PhysicsSimulation/vector.h"   // For Vector3 math

#include <stdexcept> // For potential exceptions
#include <cmath>     // For std::fabs
#include <memory>    // For std::unique_ptr, std::make_unique
#include <vector>
#include <algorithm> // For std::for_each

//namespace PhysicsSimulation {

Simulation::Simulation()
    : integrator_(std::make_unique<EulerIntegrator>()), // Default to Euler
      dissipative_coefficient_(0.5f)
{
    // Vectors are default-initialized (empty)
}

// Destructor is defaulted (unique_ptr handles cleanup)

// --- Object Addition Methods ---

void Simulation::AddPlane(std::unique_ptr<Plane> plane) {
    if (plane) {
        planes_.push_back(std::move(plane));
    }
}

void Simulation::AddParticle(std::unique_ptr<Particle> particle) {
     if (particle) {
        // Add to the non-owning list for processing
        particles_.push_back(particle.get());
        // Add to the owning list
        owned_particles_.push_back(std::move(particle));
    }
}

void Simulation::AddForceGenerator(std::unique_ptr<ForceGenerator> force_generator) {
    if (force_generator) {
        force_generators_.push_back(std::move(force_generator));
    }
}

void Simulation::AddParticleGenerator(std::unique_ptr<ParticleGenerator> particle_generator) {
    if (!particle_generator) return;

    // Add particles from the generator to the non-owning list
    for (auto& particle_ptr : particle_generator->particles()) {
         if (particle_ptr) {
            particles_.push_back(particle_ptr.get());
        }
    }
    // Store the generator itself
    particle_generators_.push_back(std::move(particle_generator));
}

void Simulation::AddCube(std::unique_ptr<Cube> cube) {
    if (!cube) return;

    // Add particles from the cube to the non-owning list
    for (Particle& p : cube->particles()) {
        particles_.push_back(&p);
    }

    // TODO: Re-evaluate spring creation logic for Cube.
    // The original code created springs between *all* pairs, which is likely
    // incorrect for a cube structure (should only be edges/diagonals).
    // This needs a specific implementation based on desired cube rigidity.
    // Example for edges only (needs refinement):
    /*
    float stiffness = 100.0f;
    float damping = 5.0f;
    auto& cube_particles = cube->particles();
    // Add springs for edges (example - needs correct indices)
    AddSpring(stiffness, damping, &cube_particles[0], &cube_particles[1]);
    AddSpring(stiffness, damping, &cube_particles[1], &cube_particles[2]);
    // ... add all 12 edges ...
    // Add springs for face/body diagonals if needed
    */

    // Store the cube
    cubes_.push_back(std::move(cube));
}

void Simulation::AddCloth(std::unique_ptr<Cloth> cloth) {
    if (!cloth) return;

    const int n_u = cloth->dim_u();
    const int n_v = cloth->dim_v();
    if (n_u <= 1 || n_v <= 1) return; // Cannot process degenerate cloth

    auto& cloth_particles = cloth->particles(); // Get reference to vector

    // Add particles from the cloth to the non-owning list
    for (Particle& p : cloth_particles) {
        particles_.push_back(&p);
    }

    // Create structural, shear, and bend springs/constraints
    float stiffness = 100.0f; // Example values
    float damping = 1.0f;

    for (int i = 0; i < n_u; ++i) {
        for (int j = 0; j < n_v; ++j) {
            Particle* p_ij = &cloth_particles[cloth->GetIndex(i, j)];

            // Structural springs (horizontal and vertical)
            if (i < n_u - 1) {
                Particle* p_i1j = &cloth_particles[cloth->GetIndex(i + 1, j)];
                float rest_length = (p_ij->position() - p_i1j->position()).Length();
                AddConstraint(rest_length, p_ij, p_i1j);
                AddSpring(stiffness, damping, p_ij, p_i1j);
            }
            if (j < n_v - 1) {
                Particle* p_ij1 = &cloth_particles[cloth->GetIndex(i, j + 1)];
                float rest_length = (p_ij->position() - p_ij1->position()).Length();
                AddConstraint(rest_length, p_ij, p_ij1);
                AddSpring(stiffness, damping, p_ij, p_ij1);
            }

            // Shear springs (diagonals)
            if (i < n_u - 1 && j < n_v - 1) {
                Particle* p_i1j1 = &cloth_particles[cloth->GetIndex(i + 1, j + 1)];
                Particle* p_i1j = &cloth_particles[cloth->GetIndex(i + 1, j)];
                Particle* p_ij1 = &cloth_particles[cloth->GetIndex(i, j + 1)];
                AddSpring(stiffness, damping, p_ij, p_i1j1); // Diagonal 1
                AddSpring(stiffness, damping, p_i1j, p_ij1); // Diagonal 2
            }

            // Bend springs (skip one particle horizontally and vertically)
            if (i < n_u - 2) {
                Particle* p_i2j = &cloth_particles[cloth->GetIndex(i + 2, j)];
                AddSpring(stiffness, damping, p_ij, p_i2j);
            }
            if (j < n_v - 2) {
                Particle* p_ij2 = &cloth_particles[cloth->GetIndex(i, j + 2)];
                AddSpring(stiffness, damping, p_ij, p_ij2);
            }
        }
    }

    // Store the cloth
    cloths_.push_back(std::move(cloth));
}


// --- Helper Methods ---

void Simulation::AddConstraint(float length, Particle* particle_a, Particle* particle_b) {
    if (particle_a && particle_b && particle_a != particle_b) {
        constraints_.push_back(std::make_unique<Constraint>(length, particle_a, particle_b));
    }
}

void Simulation::AddSpring(float stiffness, float damping, Particle* particle_a, Particle* particle_b) {
     if (particle_a && particle_b && particle_a != particle_b) {
        try {
            springs_.push_back(std::make_unique<Spring>(stiffness, damping, particle_a, particle_b));
        } catch (const std::invalid_argument& e) {
            // Handle or log the error (e.g., particles too close)
            // std::cerr << "Error adding spring: " << e.what() << std::endl;
        }
    }
}

// --- Simulation Loop Steps ---

void Simulation::UpdateSprings() {
    for (auto& spring : springs_) {
        spring->ApplyForce();
    }
}

void Simulation::UpdateConstraints() {
    // Iteratively satisfy constraints (multiple passes improve stability)
    const int constraint_iterations = 10;
    for (int i = 0; i < constraint_iterations; ++i) {
        for (auto& constraint : constraints_) {
            constraint->SatisfyConstraint();
        }
    }
}

void Simulation::ApplyForces() {
    for (Particle* p : particles_) {
        if (p && p->type() == Particle::Type::kActive) {
            for (auto& force_gen : force_generators_) {
                force_gen->ApplyForce(*p);
            }
        }
    }
}

void Simulation::IntegrateParticles(float dt) {
     if (!integrator_) {
        // Log error or throw: No integrator set
        return;
    }
    for (Particle* p : particles_) {
        if (p && p->type() == Particle::Type::kActive) {
            float mass = p->mass();
            Vector3 acceleration = (mass > 1e-9f) ? p->force_accumulator() / mass : Vector3(); // Handle zero mass

            integrator_->Integrate(acceleration, *p, dt);
        }
    }
}

void Simulation::HandleCollisions() {
    // Particle-Particle Collisions
    for (size_t i = 0; i < particles_.size(); ++i) {
        Particle* p1 = particles_[i];
        if (!p1) continue;

        for (size_t j = i + 1; j < particles_.size(); ++j) {
            Particle* p2 = particles_[j];
            if (!p2) continue;

            Vector3 delta_pos = p1->position() - p2->position();
            float dist_sq = delta_pos.SqrLength();
            float combined_radius = p1->radius() + p2->radius();
            float combined_radius_sq = combined_radius * combined_radius;

            if (dist_sq < combined_radius_sq && dist_sq > 1e-9f) { // Check collision and avoid self/coincident
                float dist = std::sqrt(dist_sq);
                Vector3 normal = delta_pos / dist; // Normalized direction from p2 to p1
                float penetration_depth = combined_radius - dist;

                // --- Positional Correction ---
                // Distribute correction based on type (similar to Constraint)
                float weight1 = 0.0f, weight2 = 0.0f;
                bool fixed1 = (p1->type() == Particle::Type::kFixed);
                bool fixed2 = (p2->type() == Particle::Type::kFixed);
                if (!fixed1 && !fixed2) { weight1 = 0.5f; weight2 = 0.5f; }
                else if (fixed1 && !fixed2) { weight2 = 1.0f; }
                else if (!fixed1 && fixed2) { weight1 = 1.0f; }

                if (weight1 > 0.0f) p1->set_position(p1->position() + normal * (penetration_depth * weight1));
                if (weight2 > 0.0f) p2->set_position(p2->position() - normal * (penetration_depth * weight2));

                // --- Velocity Correction (Simple Impulse) ---
                Vector3 relative_velocity = p1->velocity() - p2->velocity();
                float velocity_along_normal = Dot(relative_velocity, normal);

                // Only resolve if separating velocity is negative (i.e., they are moving towards each other)
                if (velocity_along_normal < 0) {
                    // Calculate impulse magnitude (simplified, assumes equal mass or uses average)
                    // A more correct calculation involves inverse masses.
                    float restitution = dissipative_coefficient_; // Treat dissipative as restitution
                    float impulse_magnitude = -(1.0f + restitution) * velocity_along_normal;

                    // Apply impulse based on type/mass (simplified: split if both active)
                    if (!fixed1 && !fixed2) {
                        Vector3 impulse = normal * (impulse_magnitude * 0.5f);
                        p1->set_velocity(p1->velocity() + impulse);
                        p2->set_velocity(p2->velocity() - impulse);
                    } else if (!fixed1 && fixed2) { // p1 active, p2 fixed
                         Vector3 impulse = normal * impulse_magnitude;
                         p1->set_velocity(p1->velocity() + impulse);
                    } else if (fixed1 && !fixed2) { // p1 fixed, p2 active
                         Vector3 impulse = normal * impulse_magnitude;
                         p2->set_velocity(p2->velocity() - impulse);
                    }
                }
            }
        }
    }

    // Particle-Plane Collisions
    for (Particle* p : particles_) {
        if (!p) continue;

        for (const auto& plane_ptr : planes_) {
            const Plane& plane = *plane_ptr;
            const Vector3& normal = plane.normal(); // Assume normalized
            // Calculate distance from particle center to plane
            float dist_to_plane = Dot(p->position() - plane.position(), normal);
            float penetration_depth = p->radius() - dist_to_plane;

            if (penetration_depth > 0.0f) { // Collision detected
                // --- Positional Correction ---
                if (p->type() != Particle::Type::kFixed) {
                    p->set_position(p->position() + normal * penetration_depth);
                }

                // --- Velocity Correction ---
                float velocity_along_normal = Dot(p->velocity(), normal);
                if (velocity_along_normal < 0) { // Moving towards plane
                    float restitution = dissipative_coefficient_;
                    Vector3 impulse = normal * (-(1.0f + restitution) * velocity_along_normal);
                     if (p->type() != Particle::Type::kFixed) {
                        p->set_velocity(p->velocity() + impulse);
                    }
                }
            }
        }
    }
}


void Simulation::ClearParticleForces() {
    for (Particle* p : particles_) {
        if (p) { // No need to check type, clearing is safe for all
            p->ClearForceAccumulator();
        }
    }
}

void Simulation::UpdateParticles(float dt) {
    // Main particle update sequence for one time step dt
    ApplyForces();       // Apply gravity, medium drag, etc.
    UpdateSprings();     // Calculate and apply spring forces
    IntegrateParticles(dt); // Update position/velocity based on forces
    UpdateConstraints(); // Enforce rigid constraints (position adjustment)
    HandleCollisions();  // Detect and resolve collisions (position/velocity adjustment)
    ClearParticleForces(); // Clear forces for the next step
}

// --- Main Update and Draw ---

void Simulation::Update(float dt) {
    // Update generators (if they create particles over time)
    for (auto& gen : particle_generators_) {
        // TODO: Implement generator update logic if needed
        // gen->Update(dt); // Might need dt
    }

    UpdateParticles(dt); // Update all particle physics
}

void Simulation::DrawPlanes() const {
    for (const auto& plane : planes_) {
        plane->Draw();
    }
}

void Simulation::DrawSprings() const {
    for (const auto& spring : springs_) {
        spring->Draw();
    }
}

void Simulation::DrawParticles() const {
    // Draw particles from all sources
    for (const Particle* p : particles_) {
        if (p) {
            p->Draw(); // Assuming Particle::Draw exists now
        }
    }
}

void Simulation::Draw() {
    DrawPlanes();
    DrawSprings();
    DrawParticles();
    // DrawConstraints(); // If constraints have visuals
}

//} // namespace PhysicsSimulation
