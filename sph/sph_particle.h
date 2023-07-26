#ifndef SPH_PARTICLE_H
#define SPH_PARTICLE_H

#include "sph_common.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <vector>

namespace sph {
struct Particle {
  // Struct constructor.
  Particle(float x, float y)
      : position(glm::vec2(x, y)), velocity(glm::vec2(0.f, 0.f)),
        force(glm::vec2(0.f, 0.f)), dense(0.f), pressure(0.f){};
  Particle(glm::vec2 pos)
      : position(pos), velocity(glm::vec2(0.f, 0.f)),
        force(glm::vec2(0.f, 0.f)), dense(0.f), pressure(0.f){};
  // Overload operators.
  bool operator==(const Particle &x) const {
    return glm::length(glm::distance(position, x.position)) < common::EPSILON;
  }
  // Properties.
  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 force;
  float r, g, b;
  float dense;
  float pressure;
};

class SPHSystem {
private:
  int max_particles;
  int init_particles;
  void compute_dense();
  void compute_force();
  void integrate();

public:
  std::vector<Particle> particles;

  SPHSystem();
  ~SPHSystem();
  void compute();
  void init();
};

// Helper functions.
std::ostream &operator<<(std::ostream &o, sph::Particle &i);
} // namespace sph

#endif