#include "graphics.h"
#include <algorithm>
#include <vulkan/vulkan_core.h>
#include <iostream>
namespace veng {

Graphics::Graphics(gsl::not_null<Window*> window) : window_(window) {
  InitilizeVulkan();
}

Graphics::~Graphics() {
  if(instance_ != nullptr) {
    vkDestroyInstance(instance_,nullptr);
  }
}


void Graphics::InitilizeVulkan() {
  CreateInstance();
}

void Graphics::CreateInstance() {
  gsl::span<gsl::czstring> suggested_extensions = GetSuggestedExtensions();
  std::vector<VkExtensionProperties> supported_extensions = GetSupportedInstanceExtensions();
  auto is_extension_supported = [&supported_extensions](gsl::czstring name) {
      return std::any_of(supported_extensions.begin(),supported.end(),[name](const VkExtensionProperties& property){
      return std::strcmp(property.extensionName,name) == 0;
    });
  }
  if(!std::all_of(suggested_extensions.begin(),suggested_extensions.end(),is_extension_supported)) {
    std::exit(EXIT_FAILURE);
  }
  VkApplicationInfo app_info = {};
  app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  app_info.pNext = nullptr;
  app_info.pApplicationName = "VK_MANDELBROT";
  app_info.applicationVersion = VK_MAKE_VERSION(1,0,0);
  app_info.pEngine = "veng";
  app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  app_info.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo instance_creation_info = {};
  instance_creation_info.sType = VK_STRUCTURE_TYPE_CREATE_INFO;
  instance_creation_info.pNext = nullptr;
  instance_creation_info.pApplicationInfo = &app_info;
  instance_creation_info.enabledExtensionCount = suggested_extensions.size();
  instance_creation_info.ppEnabledExtensionNames = suggested_extensions.data();
  instance_creation_info.enabledLayerCount = 0;

  VkResult result = vkCreateInstance(&instance_creation_info,nullptr,&instance);
  if(result != VK_SUCCESS) {
    std::exit(EXIT_FAILURE);
  }


}



std::vector<VkExtensionProperties> Graphics::GetSupportedInstanceExtensions() {
  std::uint32_t count;
  vkEnumerateInstanceExtensionProperties(nullptr,&count,nullptr);
  if(count ==0) {
    return {};
  }
  std::vector<VkExtensionProperties> properties(count);
  vkEnumerateInstanceExtensionProperties(nullptr,&count,properties.data());
  return properties;
}

gsl::span<gsl::czstring> Graphics::GetSuggestedExtensions() {
  std::uint32_t glfwExtensionCount = 0;
  gsl::czstring *glfwExtensions;
  glfwExtensions = gflwGetRequiredInstanceExtensions(&glfwExtensionCount);
  return {glfw_extensions,glfw_extension_count};

}   
}
