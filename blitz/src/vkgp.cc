#include "blitz/vkgp/vkgp.hpp"
#include <vector>

#ifndef NDEBUG
const bool enable_validation_layer = false;
#else
const bool enable_validation_layer = true;
#endif

const std::vector<const char *> validation_layers{
    "VK_LAYER_KHRONOS_validation_layer"};

const std::vector<const char *> device_extensions{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME};

bool vkgp::queue_family_indices::is_complete() {
  return graphics_family.has_value() && present_family.has_value();
}

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

VkExtent2D vkgp::demo_application::choose_swap_extent(
    const VkSurfaceCapabilitiesKHR &capabilities) {
  if (capabilities.currentExtent.width != UINT32_MAX) {
    return capabilities.currentExtent;
  } else {
    VkExtent2D actual_extent = {static_cast<uint32_t>(WIDTH), static_cast<uint32_t>(HEIGHT)};
    actual_extent.width = std::max(
        capabilities.minImageExtent.width,
        std::min(capabilities.maxImageExtent.width, actual_extent.width));
    actual_extent.height = std::max(
        capabilities.minImageExtent.height,
        std::min(capabilities.maxImageExtent.height, actual_extent.height));

    return actual_extent;
  }
}

VkSurfaceFormatKHR vkgp::demo_application::choose_swap_surface_format(
    std::vector<VkSurfaceFormatKHR> &available_formats) {
  for (const auto &available_format : available_formats) {
    if (available_format.format == VK_FORMAT_B8G8R8A8_SRGB &&
        available_format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
      return available_format;
    }
  }
  return available_formats[0];
}

VkPresentModeKHR vkgp::demo_application::choose_swap_present_mode(
    const std::vector<VkPresentModeKHR> &available_present_modes) {
  for (const auto &mode : available_present_modes) {
    if (mode == VK_PRESENT_MODE_MAILBOX_KHR) {
      return mode;
    }
  }
  return VK_PRESENT_MODE_FIFO_KHR;
}

bool vkgp::demo_application::check_device_extension_support(
    VkPhysicalDevice _device) {
  uint32_t extension_count;
  vkEnumerateDeviceExtensionProperties(_device, nullptr, &extension_count,
                                       nullptr);

  std::vector<VkExtensionProperties> available_extensions(extension_count);
  vkEnumerateDeviceExtensionProperties(_device, nullptr, &extension_count,
                                       available_extensions.data());

  std::set<std::string> required_extensions{device_extensions.begin(),
                                            device_extensions.end()};

  for (const auto &ext : available_extensions)
    required_extensions.erase(ext.extensionName);

  return required_extensions.empty();
}

void vkgp::demo_application::create_instance() {
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

void vkgp::demo_application::create_logical_device() {
  auto indices = find_queue_families(physical_device);
  // Specifying the queues to be created.
  std::vector<VkDeviceQueueCreateInfo> queue_create_infos;
  std::set<uint32_t> unique_queue_families{indices.graphics_family.value(),
                                           indices.present_family.value()};
  // Setting queue priority
  float queue_priority = 1.0f;

  for (uint32_t q_family : unique_queue_families) {
    VkDeviceQueueCreateInfo queue_create_info{};
    queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queue_create_info.queueFamilyIndex = q_family;
    queue_create_info.queueCount = 1;
    queue_create_info.pQueuePriorities = &queue_priority;
    queue_create_infos.push_back(queue_create_info);
  }
  // Specifying used device features
  VkPhysicalDeviceFeatures device_features{};
  // Creating the logical device
  VkDeviceCreateInfo create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  create_info.pQueueCreateInfos = queue_create_infos.data();
  create_info.queueCreateInfoCount =
      static_cast<uint32_t>(queue_create_infos.size());
  create_info.pEnabledFeatures = &device_features;
  create_info.enabledExtensionCount =
      static_cast<uint32_t>(device_extensions.size());
  create_info.ppEnabledExtensionNames = device_extensions.data();

  if (enable_validation_layer) {
    create_info.enabledLayerCount =
        static_cast<uint32_t>(validation_layers.size());
    create_info.ppEnabledLayerNames = validation_layers.data();
  } else {
    create_info.enabledLayerCount = 0;
  }
  // Instantiate logical device
  if (vkCreateDevice(physical_device, &create_info, nullptr, &device) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create logical device.");
  }

  // Retrieve queue handle;
  vkGetDeviceQueue(device, indices.graphics_family.value(), 0, &graphics_queue);
  vkGetDeviceQueue(device, indices.present_family.value(), 0, &present_queue);
}

void vkgp::demo_application::create_surface() {
  if (glfwCreateWindowSurface(instance, window, nullptr, &surface) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create window surface.");
  }
}

void vkgp::demo_application::create_swap_chain() {
  auto swap_chain_support_details = query_swap_chain_support(physical_device);
  auto surface_format =
      choose_swap_surface_format(swap_chain_support_details.format);
  auto present_mode =
      choose_swap_present_mode(swap_chain_support_details.present_modes);
  auto extent = choose_swap_extent(swap_chain_support_details.capabilities);

  uint32_t image_count =
      swap_chain_support_details.capabilities.minImageCount + 1;
  if (swap_chain_support_details.capabilities.maxImageCount > 0 &&
      image_count > swap_chain_support_details.capabilities.maxImageCount) {
    image_count = swap_chain_support_details.capabilities.maxImageCount;
  }

  VkSwapchainCreateInfoKHR create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  create_info.surface = surface;
  create_info.minImageCount = image_count;
  create_info.imageColorSpace = surface_format.colorSpace;
  create_info.imageFormat = surface_format.format;
  create_info.imageExtent = extent;
  create_info.imageArrayLayers = 1;
  create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

  auto indices = find_queue_families(physical_device);
  uint32_t queue_family_idx[]{indices.graphics_family.value(),
                              indices.present_family.value()};

  if (indices.graphics_family != indices.present_family) {
    create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    create_info.queueFamilyIndexCount = 2;
    create_info.pQueueFamilyIndices = queue_family_idx;
  } else {
    create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    create_info.queueFamilyIndexCount = 0;     // Optional
    create_info.pQueueFamilyIndices = nullptr; // Optional
  }

  create_info.preTransform =
      swap_chain_support_details.capabilities.currentTransform;
  create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  create_info.presentMode = present_mode;
  create_info.clipped = VK_TRUE;
  create_info.oldSwapchain = VK_NULL_HANDLE;

  if (vkCreateSwapchainKHR(device, &create_info, nullptr, &swap_chain) !=
      VK_SUCCESS) {
    throw std::runtime_error("failed to create swap chain.");
  }
  vkGetSwapchainImagesKHR(device, swap_chain, &image_count, nullptr);
  swapchain_images.resize(image_count);
  vkGetSwapchainImagesKHR(device, swap_chain, &image_count, swapchain_images.data());
  swapchain_image_format = surface_format.format;
  swapchain_image_extent = extent;
}

// message callback
VKAPI_ATTR VkBool32 VKAPI_CALL vkgp::demo_application::debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
    VkDebugUtilsMessageTypeFlagsEXT message_type,
    const VkDebugUtilsMessengerCallbackDataEXT *p_callback_data,
    void *p_user_data) {
  std::cerr << "validation layer:\t" << p_callback_data->pMessage << std::endl;

  return VK_FALSE;
}

void vkgp::demo_application::run() {
  init_window();
  init_vulkan();
  main_loop();
  cleanup();
}

void vkgp::demo_application::cleanup() {

  if (enable_validation_layer)
    destroy_debug_utils_messenger_ext(instance, debug_messenger, nullptr);

  vkDestroySwapchainKHR(device, swap_chain, nullptr);

  vkDestroyDevice(device, nullptr);

  vkDestroySurfaceKHR(instance, surface, nullptr);

  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);

  glfwTerminate();
}

vkgp::queue_family_indices
vkgp::demo_application::find_queue_families(VkPhysicalDevice _device) {
  queue_family_indices indices;
  VkBool32 present_support = false;
  uint32_t count = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(_device, &count, nullptr);
  std::vector<VkQueueFamilyProperties> queue_families(count);
  vkGetPhysicalDeviceQueueFamilyProperties(_device, &count,
                                           queue_families.data());
  uint32_t i = 0;
  for (const auto &q_family : queue_families) {
    vkGetPhysicalDeviceSurfaceSupportKHR(_device, i, surface, &present_support);
    if (q_family.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.graphics_family = i;
    }
    if (present_support) {
      indices.present_family = i;
    }
    if (indices.is_complete()) {
      break;
    }
    ++i;
  }

  return indices;
}

void vkgp::demo_application::init_vulkan() {
  create_instance();
  setup_debug_messenger();
  create_surface();
  select_physical_device();
  create_logical_device();
  create_swap_chain();
}

void vkgp::demo_application::init_window() {

  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void vkgp::demo_application::main_loop() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void vkgp::demo_application::populate_debug_messenger_create_info(
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

void vkgp::demo_application::select_physical_device() {
  uint32_t count = 0;
  vkEnumeratePhysicalDevices(instance, &count, nullptr);
  if (count == 0)
    throw std::runtime_error("failed to find GPUs with Vulkan support.");

  std::vector<VkPhysicalDevice> devices(count);
  vkEnumeratePhysicalDevices(instance, &count, devices.data());

  for (const auto &dev : devices) {
    if (is_suitable(dev)) {
      physical_device = dev;
      break;
    }
  }
  if (physical_device == VK_NULL_HANDLE)
    throw std::runtime_error("failed to find a suitable GPU.");
}

bool vkgp::demo_application::is_suitable(VkPhysicalDevice _device) {
  auto indices = find_queue_families(_device);
  bool extension_supported = check_device_extension_support(_device);
  bool swapchain_adequate = false;
  if (extension_supported) {
    auto swapchain_support = query_swap_chain_support(_device);
    swapchain_adequate = !swapchain_support.format.empty() &&
                         !swapchain_support.present_modes.empty();
  }

  return indices.is_complete() && extension_supported && swapchain_adequate;
}

void vkgp::demo_application::setup_debug_messenger() {

  if (!enable_validation_layer)
    return;
  VkDebugUtilsMessengerCreateInfoEXT create_info{};
  populate_debug_messenger_create_info(create_info);

  if (create_debug_utils_messenger_ext(instance, &create_info, nullptr,
                                       &debug_messenger) != VK_SUCCESS)
    throw std::runtime_error("failed to create debug messenger!");
}

vkgp::swapchain_support_details
vkgp::demo_application::query_swap_chain_support(VkPhysicalDevice _device) {
  swapchain_support_details details;

  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_device, surface,
                                            &details.capabilities);

  uint32_t format_count;
  vkGetPhysicalDeviceSurfaceFormatsKHR(_device, surface, &format_count,
                                       nullptr);
  if (format_count != 0) {
    details.format.resize(format_count);
    vkGetPhysicalDeviceSurfaceFormatsKHR(_device, surface, &format_count,
                                         details.format.data());
  }

  uint32_t present_mode_count;
  vkGetPhysicalDeviceSurfacePresentModesKHR(_device, surface,
                                            &present_mode_count, nullptr);
  if (present_mode_count != 0) {
    details.present_modes.resize(present_mode_count);
    vkGetPhysicalDeviceSurfacePresentModesKHR(
        _device, surface, &present_mode_count, details.present_modes.data());
  }

  return details;
}
