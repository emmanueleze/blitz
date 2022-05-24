#include "blitz/vkgp/vkgp.hpp"
#include <vector>

#ifndef NDEBUG
const bool enable_validation_layer = false;
#else
const bool enable_validation_layer = true;
#endif

const std::vector<const char *> validation_layers{
    "VK_LAYER_KHRONOS_validation_layer"};

bool vkgp::check_validation_layer_support() {
  uint32_t layer_count;
  vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

  std::vector<VkLayerProperties> available_layers(layer_count);
  vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

  // Check if all of the layers exists in available_layers list
  for (auto _layer_name : validation_layers) {
    bool found = false;

    for (const auto &_layer_properties : available_layers) {
      if (strcmp(_layer_name, _layer_properties.layerName) == 0) {
        found = true;
        break;
      }
    }
    if (!found)
      return false;
  }
  return true;
}

std::vector<const char *> vkgp::get_required_extensions() {
  uint32_t glfw_ext_count = 0;
  auto glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_ext_count);

  std::vector<const char *> extensions(glfw_extensions,
                                       glfw_extensions + glfw_ext_count);
  if (enable_validation_layer) {
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  }
  return extensions;
}

VkResult vkgp::create_debug_utils_messenger_ext(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *p_create_info,
    const VkAllocationCallbacks *p_allocator,
    VkDebugUtilsMessengerEXT *p_debug_messenger) {
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, p_create_info, p_allocator, p_debug_messenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

void vkgp::destroy_debug_utils_messenger_ext(
    VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks *p_allocator) {
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, p_allocator);
  }
}

void vkgp::hello_triangle_application::create_instance() {
  if (enable_validation_layer && !check_validation_layer_support()) {
    throw std::runtime_error("validation layers requested but not available");
  }
  VkApplicationInfo app_info{};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pApplicationName = "Hello Triangle";
  app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.pEngineName = "No Engine";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo create_info;
  create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  create_info.pApplicationInfo = &app_info;

  if (enable_validation_layer) {
    create_info.enabledLayerCount =
        static_cast<uint32_t>(validation_layers.size());
    create_info.ppEnabledLayerNames = validation_layers.data();
  } else {
    create_info.enabledLayerCount = 0;
  }

  auto extension = get_required_extensions();

  create_info.enabledExtensionCount = static_cast<uint32_t>(extension.size());
  create_info.ppEnabledExtensionNames = extension.data();

  auto result = vkCreateInstance(&create_info, nullptr, &instance);
  if (result != VK_SUCCESS)
    throw std::runtime_error("failed to create instance.");
}

// message callback
VKAPI_ATTR VkBool32 VKAPI_CALL vkgp::hello_triangle_application::debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
    void *p_user_data) {
  std::cerr << "validation layer:\t" << p_callback_data->pMessage << std::endl;

  return VK_FALSE;
}

void vkgp::hello_triangle_application::run() {
  init_vulkan();
  init_window();
  main_loop();
  cleanup();
}

void vkgp::hello_triangle_application::cleanup() {

  if (enable_validation_layer)
    destroy_debug_utils_messenger_ext(instance, debug_messenger, nullptr);

  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);

  glfwTerminate();
}

void vkgp::hello_triangle_application::init_vulkan() { create_instance(); }

void vkgp::hello_triangle_application::init_window() {

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void vkgp::hello_triangle_application::main_loop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void vkgp::hello_triangle_application::populate_debug_messenger_create_info(
    VkDebugUtilsMessengerCreateInfoEXT &create_info) {
  create_info = {};
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity =
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
      VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  create_info.pfnUserCallback = debug_callback;
}

void vkgp::hello_triangle_application::setup_debug_messenger() {
  if (!enable_validation_layer)
    return;
  VkDebugUtilsMessengerCreateInfoEXT create_info{};
  populate_debug_messenger_create_info(create_info);
  
  if (create_debug_utils_messenger_ext(instance, &create_info, nullptr,
                                       &debug_messenger) != VK_SUCCESS)
    throw std::runtime_error("failed to create debug messenger!");
}