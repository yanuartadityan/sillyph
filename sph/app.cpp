#include "app.h"
#include "sph_particle.h"

// clang-format off
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// clang-format on

#define GLFW_MAJOR_VER 3
#define GLFW_MINOR_VER 3

using namespace app;

App::App() {
  this->screen_x = 1280;
  this->screen_y = 1024;
}

App::App(int x, int y) {
  this->screen_x = x;
  this->screen_y = y;
}

void App::process_input() {
  if (glfwGetKey(this->main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(this->main_window, true);
}

void App::glfw_error_callback(int error, const char *desc) {
  fprintf(stderr, "GLFW error %d: %s\n", error, desc);
}

void App::glfw_fb_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void App::draw(sph::SPHSystem &sph) {
  float aspect_ratio;
  int width, height;
  glfwGetFramebufferSize(this->main_window, &width, &height);
  aspect_ratio = width / (float)height;
  glViewport(0, 0, width, height);

  // glClearColor(.2f, .3f, .3f, 1.0f);
  glClearColor(0.090196, 0.113725, 0.137255, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, 0, height, -1, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Draw particles.
  glEnable(GL_POINT_SMOOTH);
  glPointSize(10);
  glVertexPointer(2, GL_FLOAT, sizeof(sph::Particle),
                  &sph.particles[0].position);
  glColorPointer(3, GL_FLOAT, sizeof(sph::Particle), &sph.particles[0].color);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(sph.particles.size()));
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
}

int App::render_simulation(sph::SPHSystem &sph) {
  // set opengl/glfw version hint.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_MAJOR_VER);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR_VER);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfw error callback.
  glfwSetErrorCallback(this->glfw_error_callback);

  // init glfw.
  if (!glfwInit()) {
    std::cout << "Failed on initializing GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  // create window instance.
  this->main_window =
      glfwCreateWindow(this->screen_x, this->screen_y, "SillySPH", NULL, NULL);

  // allow user to resize window to a minimum limit.
  glfwSetWindowSizeLimits(this->main_window, 320, 240, GLFW_DONT_CARE,
                          GLFW_DONT_CARE);

  // set main window as active.
  glfwMakeContextCurrent(this->main_window);

  // enable v-sync (1).
  glfwSwapInterval(1);

  // init GLAD.
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  // framebuffer callback enabled for the main window.
  glfwSetFramebufferSizeCallback(this->main_window,
                                 this->glfw_fb_size_callback);

  // SPH part.
  sph.init();

  while (!glfwWindowShouldClose(this->main_window)) {
    // User input.
    this->process_input();

    // Compute with predefined step duration per frame.
    sph.compute();

    // Rendering.
    this->draw(sph);

    // Poll events and finally, swap buffer.
    glfwSwapBuffers(this->main_window);
    glfwPollEvents();
  }

  glfwDestroyWindow(this->main_window);
  glfwTerminate();
  return EXIT_SUCCESS;
}