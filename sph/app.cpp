#include "app.h"
#include "sph_particle.h"

// clang-format off
#include <cstdlib>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
// clang-format on

using namespace app;

App::App() {
  this->screen_x = 1280;
  this->screen_y = 1024;
}

App::App(int x, int y) {
  this->screen_x = x;
  this->screen_y = y;
}

int App::init_glfw(int major, int minor) {
  glfwSetErrorCallback(this->glfw_error_callback);

  if (!glfwInit())
    return EXIT_FAILURE;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  this->main_window = glfwCreateWindow(this->screen_x, this->screen_y,
                                       "SillyPH App", nullptr, nullptr);

  return EXIT_SUCCESS;
}

int App::init_glad() {
#if __APPLE__
  gladLoadGL();
#else
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#endif

  return EXIT_SUCCESS;
}

void App::set_context_window(GLFWwindow *handle) {
  glfwMakeContextCurrent(handle);
}

void App::process_input() {
  if (glfwGetKey(this->main_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(this->main_window, true);
}

void App::set_vsync(int vsync_state) { glfwSwapInterval(vsync_state); }

void App::set_viewport(int x_origin, int y_origin) {
  // set the viewport
  glViewport(x_origin, y_origin, this->screen_x, this->screen_y);
}

void App::set_buffers(float *input_vertices, size_t vertices_size) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and
  // then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices_size, input_vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                        (void *)nullptr);
  glEnableVertexAttribArray(0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO
  // as the vertex attribute's bound vertex buffer object so afterwards we can
  // safely unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // You can unbind the VAO afterwards so other VAO calls won't accidentally
  // modify this VAO, but this rarely happens. Modifying other VAOs requires a
  // call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
  // VBOs) when it's not directly necessary.
  glBindVertexArray(0);
}

void App::glfw_error_callback(int error, const char *desc) {
  fprintf(stderr, "GLFW error %d: %s\n", error, desc);
}

void App::glfw_fb_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void App::draw(sph::SPHSystem &sph) {
  glClearColor(.7f, .1f, .1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  int width, height;
  glfwGetWindowSize(this->main_window, &width, &height);
  // this->set_viewport(0, 0);
  glViewport(0, 0, 1280, 1024);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // const double ar = width / (double)height;
  // glOrtho(ar * -1.f * common::VIEW_WIDTH, ar * common::VIEW_WIDTH, 0,
  //         2 * common::VIEW_WIDTH, -1.f, 1.f);
  glOrtho(0.f, common::WINDOW_WIDTH, common::WINDOW_HEIGHT, 0.f, 0.f, 1.f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Draw particles.
  // glPointSize(common::h * 2.f);
  glPointSize(30);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColor4f(1, 1, 1, 1);
  glVertexPointer(2, GL_FLOAT, 24, &sph.particles[0].position);
  glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(sph.particles.size()));
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  glDisableClientState(GL_VERTEX_ARRAY);
}

int App::render_simulation(sph::SPHSystem &sph) {
  if (this->init_glfw(3, 3)) {
    std::cout << "Failed on initializing GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  this->set_context_window(this->main_window);
  this->set_vsync(true);

  if (this->init_glad()) {
    std::cout << "Failed on initializing GLAD" << std::endl;
    return EXIT_FAILURE;
  }

  glfwSwapInterval(1);

  glfwSetFramebufferSizeCallback(this->main_window,
                                 this->glfw_fb_size_callback);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // SPH part.
  // sph.init();
  glm::vec2 point1(0.f, 0.f);
  glm::vec2 point2(50.f, 50.f);
  glm::vec2 point3(100.f, 100.f);
  sph.particles.push_back(point1);
  sph.particles.push_back(point2);
  sph.particles.push_back(point3);

  while (!glfwWindowShouldClose(this->main_window)) {
    // User input.
    this->process_input();

    // Compute with predefined step duration per frame.
    // sph.compute();

    // Rendering.
    this->draw(sph);

    // Poll events and finally, swap buffer.
    glfwPollEvents();
    glfwSwapBuffers(this->main_window);
  }

  glfwTerminate();
  return EXIT_SUCCESS;
}