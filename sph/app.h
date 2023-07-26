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
  bool show_window = true, show_theme = true, show_another = false;
  unsigned int VAO = 0, VBO = 0;

public:
  App();
  App(int, int);

  int init_glfw(int major, int minor);
  int init_glad();
  void process_input();
  void set_context_window(GLFWwindow *);
  void set_vsync(int);
  void set_viewport(int x_origo, int y_origo);
  void set_buffers(float *vertices, size_t vertice_size);

  // sph
  void draw(sph::SPHSystem &sph);
  int render_simulation(sph::SPHSystem &sph);

  // static
  static void glfw_error_callback(int error, const char *desc);
  static void glfw_fb_size_callback(GLFWwindow *window, int width, int height);
};
} // namespace app
#endif