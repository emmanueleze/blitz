#ifndef BLITZ_INCLUDE_BLITZ_VKGP_VKGP_HPP
#define BLITZ_INCLUDE_BLITZ_VKGP_VKGP_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <optional>
#include <set>
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

struct queue_family_indices {
  std::optional<uint32_t> graphics_family;
  std::optional<uint32_t> present_family;

  bool is_complete();
};

struct swapchain_support_details {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> format;
  std::vector<VkPresentModeKHR> present_modes;
};

class demo_application {
public:
  void run();

private:
  VkSurfaceFormatKHR
  choose_swap_surface_format(std::vector<VkSurfaceFormatKHR> &);
  VkPresentModeKHR
  choose_swap_present_mode(const std::vector<VkPresentModeKHR> &);
  VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR &);
  void cleanup();
  void create_image_views();
  void create_instance();
  void create_logical_device();
  void create_surface();
  void create_swap_chain();
  void init_vulkan();
  void init_window();
  void main_loop();
  void setup_debug_messenger();
  void select_physical_device();
  bool check_device_extension_support(VkPhysicalDevice);
  queue_family_indices find_queue_families(VkPhysicalDevice);
  // message callback
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
                 VkDebugUtilsMessageTypeFlagsEXT message_type,
                 const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
                 void *p_user_data);
  void
  populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &);
  bool is_suitable(VkPhysicalDevice);
  swapchain_support_details query_swap_chain_support(VkPhysicalDevice);

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debug_messenger;
  VkPhysicalDevice physical_device = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphics_queue;
  VkSurfaceKHR surface;
  VkQueue present_queue;
  VkSwapchainKHR swap_chain;
  std::vector<VkImage> swapchain_images;
  VkFormat swapchain_image_format;
  VkExtent2D swapchain_image_extent;
  std::vector<VkImageView> swapchain_image_views;
  GLFWwindow *window;
  int WIDTH = 800;
  int HEIGHT = 600;
};

} // namespace vkgp

#endif