#ifndef BLITZ_INCLUDE_BLITZ_VKGP_VKGP_HPP
#define BLITZ_INCLUDE_BLITZ_VKGP_VKGP_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.hpp>

namespace vkgp {

void test_window();

// Inititalize the Vulkan library.
// This function creates an instance.
void create_instance();

class hello_triangle_application {
public:
  void run();

private:
  void cleanup();
  void create_instance();
  void init_vulkan();
  void init_window();
  void main_loop();
private:
  VkInstance instance;
  GLFWwindow *window;
  int WIDTH = 800;
  int HEIGHT = 600;
};

} // namespace vkgp

#endif