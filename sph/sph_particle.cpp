#include "sph_particle.h"

#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iomanip>
#include <iostream>

std::ostream &sph::operator<<(std::ostream &o, sph::Particle &i) {
  o << "  Particle: " << std::endl;
  o << std::fixed << std::setprecision(2);
  o << "  p: {" << i.position[0] << ", " << i.position[1] << "}" << std::endl;
  o << "  v: {" << i.velocity[0] << ", " << i.velocity[1] << "}" << std::endl;
  o << "  f: {" << i.force[0] << ", " << i.force[1] << "}" << std::endl;
  o << "  dense: " << i.dense << std::endl;
  o << "  press: " << i.pressure;

  return o;
}

sph::SPHSystem::SPHSystem()
    : max_particles(common::MAX_PARTICLES),
      init_particles(common::DAM_PARTICLES) {
  std::cout << "Constructing..." << std::endl;
}

sph::SPHSystem::~SPHSystem() { std::cout << "Deconstructing..." << std::endl; }

void sph::SPHSystem::init() {
  std::cout << "Inside init..." << std::endl;
  for (auto y = common::eps; y <= common::VIEW_HEIGHT - common::eps * 2.f;
       y += common::h) {
    for (auto x = common::VIEW_WIDTH / 4; x < common::VIEW_WIDTH;
         x += common::h) {
      if (this->particles.size() < this->init_particles) {
        Particle temp;
        float jitter =
            static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        temp.position = {x + jitter, y + jitter};
        temp.velocity = {0.f, 0.f};
        temp.color = {0.5, 1, 0};
        temp.force = {0.f, 0.f};
        this->particles.push_back(temp);
      }
    }
  }
  std::cout << "Succesfully adding " << this->particles.size()
            << " particles in the simulation." << std::endl;
}

void sph::SPHSystem::compute_dense() {
  for (sph::Particle &i : this->particles) {
    i.dense = 0.f;
    for (auto &n : this->particles) {
      float dist = glm::length(glm::distance(n.position, i.position));
      if (dist < common::hsq) {
        i.dense +=
            common::p_mass * common::poly6 * glm::pow(common::hsq - dist, 3.f);
      }
    }
    i.pressure = common::gas_const * (i.dense - common::rest_density);
  }
}

void sph::SPHSystem::compute_force() {
  for (sph::Particle &i : this->particles) {
    glm::vec2 f_press(0.f, 0.f);
    glm::vec2 f_visco(0.f, 0.f);
    for (sph::Particle &n : this->particles) {
      // If compared particles are actually same object, skip.
      if (&i == &n) {
        continue;
      }
      glm::vec2 delta_pos = n.position - i.position;
      float dist = glm::length(delta_pos);
      if (dist < common::h) {
        // Compute pressure force contribution.
        f_press += -glm::normalize(delta_pos) * common::p_mass *
                   (i.pressure + n.pressure) / (2.f * n.dense) *
                   common::spiky_grad * glm::pow(common::h - dist, 3.f);
        // Compute viscosity force contribution.
        f_visco += common::p_visc * common::p_mass * (n.velocity - i.velocity) /
                   n.dense * common::visc_lap * (common::h - dist);
      }
    }
    glm::vec2 f_grav = common::gravity * common::p_mass / (float)i.dense;
    i.force = f_press + f_visco + f_grav;
  }
}

void sph::SPHSystem::integrate() {
  for (auto &p : this->particles) {
    // Forward Euler integration.
    p.velocity += common::dt * p.force / (float)p.dense;
    p.position += common::dt * p.velocity;

    // Boundary condition.
    if (p.position.x - common::eps < 0.f) {
      p.velocity.x *= common::bound_damping;
      p.position.x = common::eps;
    }
    if (p.position.y - common::eps < 0.f) {
      p.velocity.y *= common::bound_damping;
      p.position.y = common::eps;
    }
    if (p.position.x + common::eps > common::VIEW_WIDTH) {
      p.velocity.x *= common::bound_damping;
      p.position.x = common::VIEW_WIDTH - common::eps;
    }
    if (p.position.y + common::eps > common::VIEW_WIDTH) {
      p.velocity.y *= common::bound_damping;
      p.position.y = common::VIEW_HEIGHT - common::eps;
    }
  }
}

void sph::SPHSystem::compute() {
  this->compute_dense();
  this->compute_force();
  this->integrate();
}