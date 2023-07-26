#ifndef SPH_UTILS_H
#define SPH_UTILS_H

#include <glm/gtc/constants.hpp>
#include <glm/vec2.hpp>
#include <math.h>

namespace common {
template <typename T> struct Vector2 {
  T x;
  T y;
};

// Simulation particle count common variables.
const static int MAX_PARTICLES = 2500;
const static int DAM_PARTICLES = 1000;
const static int BLOCK_PARTICLES = 250;

// Smallest different considered as equals.
const static double EPSILON = 0.00001;

// Simulation SPH solver parameters.
const static float gravity_scalar = 9.8f;
const static glm::vec2 gravity(0.f, -gravity_scalar);
const static float rest_density = 3.f;
const static float gas_const = 2.f;
const static float h = 16.f;
const static float hsq = h * h;
const static float p_mass = 2.5f;
const static float p_visc = 200.f;
const static float dt = 0.001;

// Simulation SPH smoothing kernels.
const static float poly6 = 4.f / (glm::pi<float>() * pow(h, 8.f));
const static float spiky_grad = -gravity_scalar / (M_PI * pow(h, 5.f));
const static float visc_lap = 40.f / (M_PI * pow(h, 5.f));

// Simulation bondary condition.
const static float eps = 1.0 * h;
const static float bound_damping = -0.6f;

// Simulation window variables.
const static int WINDOW_WIDTH = 1280;
const static int WINDOW_HEIGHT = 1024;
const static double VIEW_WIDTH = 1.5 * WINDOW_WIDTH;
const static double VIEW_HEIGHT = 1.5 * WINDOW_HEIGHT;
}; // namespace common

#endif