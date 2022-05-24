#include "blitz/vkgp/vkgp.hpp"
#include <vector>

void vkgp::hello_triangle_application::create_instance() {
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

  uint32_t extension_count = 0;
  const char **extensions;

  extensions = glfwGetRequiredInstanceExtensions(&extension_count);
  
  create_info.enabledExtensionCount = extension_count;
  create_info.ppEnabledExtensionNames = extensions;
  create_info.enabledLayerCount = 0;

  auto result = vkCreateInstance(&create_info, nullptr, &instance);
  if(result != VK_SUCCESS)
    throw std::runtime_error("failed to create instance.");
  
  uint32_t count;
  vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
  std::vector<VkExtensionProperties> coll(count);
  vkEnumerateInstanceExtensionProperties(nullptr, &count, coll.data());
  std::cout << "available extensions:\n";
  for(const auto& e : coll) {
    std::cout << "\t" << e.extensionName << "-"<< e.specVersion << std::endl;
  }

}

void vkgp::hello_triangle_application::run() {
  init_vulkan();
  init_window();
  main_loop();
  cleanup();
}

void vkgp::hello_triangle_application::cleanup() {
  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(window);

  glfwTerminate();
}

void vkgp::hello_triangle_application::init_vulkan() {
  create_instance();
}

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