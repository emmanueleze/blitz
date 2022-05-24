#ifndef BLITZ_INCLUDE_BLITZ_VKGP_VKGP_HPP
#define BLITZ_INCLUDE_BLITZ_VKGP_VKGP_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vulkan/vulkan.hpp>

namespace vkgp {

void test_window();

// Inititalize the Vulkan library.
// This function creates an instance.
void create_instance();

// Checks if all the requested layers are available.
bool check_validation_layer_support();

// Returns the required list of extensions.
std::vector<const char *> get_required_extensions();

VkResult create_debug_utils_messenger_ext(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger);

void destroy_debug_utils_messenger_ext(VkInstance instance,
                                       VkDebugUtilsMessengerEXT debugMessenger,
                                       const VkAllocationCallbacks *pAllocator);

class hello_triangle_application {
public:
  void run();

private:
  void cleanup();
  void create_instance();
  void init_vulkan();
  void init_window();
  void main_loop();
  void setup_debug_messenger();
  // message callback
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                 VkDebugUtilsMessageTypeFlagsEXT message_type,
                 const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
                 void *p_user_data);
  void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &);

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debug_messenger;
  GLFWwindow *window;
  int WIDTH = 800;
  int HEIGHT = 600;
};

} // namespace vkgp

#endif