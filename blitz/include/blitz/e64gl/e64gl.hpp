#ifndef BLITZ_INCLUDE_BLITZ_E64GL_E64GL_HPP
#define BLITZ_INCLUDE_BLITZ_E64GL_E64GL_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "shader.hpp"
#include "window.hpp"

#include <iostream>
#include <cmath>


namespace e64gl {
  
  // resize callback function
  void framebuffer_size_callback(GLFWwindow * window, int width, int height);

  void render_loop(GLFWwindow* window);

  void process_input(GLFWwindow *window);

  GLFWwindow *initialize_window();

  GLchar *load_shader_from_file(GLchar* path);

  void transient_green_triangle(GLuint program, const char  *);

  int windowing();
  
}

#endif  //  STRAGL_INCLUDE_STRAGL_H_