#ifndef APP_H
#define APP_H

// clang-format off
#include "sph_particle.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace app {
class App {
private:
  int screen_x, screen_y;
  GLFWwindow *main_window = nullptr;

public:
  App();
  App(int, int);

  // handle user input.
  void process_input();

  // sph
  void draw(sph::SPHSystem &sph);
  int render_simulation(sph::SPHSystem &sph);

  // static
  static void glfw_error_callback(int error, const char *desc);
  static void glfw_fb_size_callback(GLFWwindow *window, int width, int height);
};
} // namespace app
#endif