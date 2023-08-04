#ifndef SPH_PARTICLE_H
#define SPH_PARTICLE_H

#include "sph_common.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/vec2.hpp>
#include <iostream>
#include <vector>

namespace sph {
struct Particle {
  // Properties.
  glm::vec2 position;
  glm::vec2 velocity;
  glm::vec2 force;
  glm::vec3 color;
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