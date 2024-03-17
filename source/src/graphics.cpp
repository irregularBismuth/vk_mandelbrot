#include "graphics.h"
#include "utils.h"
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <gsl/string_span>
#include <vulkan/vulkan_core.h>
namespace veng {

Graphics::Graphics(gsl::not_null<Window*> window) : window_(window) {

  validation_enabled_ = true; 

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

bool Graphics::AllExtensionsSupported(gsl::span<gsl::czstring> extensions) {
  std::vector<VkExtensionProperties> supported_extensions = GetSupportedInstanceExtensions();
  return std::all_of(extensions.begin(),extensions.end(),std::bind_front(IsExtensionSupported,supported_extensions)));
}   


bool Graphics::IsExtensionSupported(gsl::span<VkExtensionProperties> extensions,gsl::czstring name) {
  return std::any_of(
    extensions.begin(),extensions.end(),std::bind_front(ExtensionMatchesName,name)
  );
}  

bool Graphics::ExtensionMatchesName(gsl::czstring name,const VkExtensionProperties& extension) {
  return veng::streq(extension.extensionName,name);
} 

void Graphics::CreateInstance() {
  std::vector<gsl::czstring> required_extensions = GetRequiredInstanceExtensions();
  
  std::array<gsl::czstring, 1> validation_layers = {"VK_LAYER_KHRONOS_validation"};
  if(!AllLayersSupported(validation_layers)) {
    validation_enabled_ = false;
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
  instance_creation_info.enabledExtensionCount = required_extensions.size();
  instance_creation_info.ppEnabledExtensionNames = required_extensions.data();
    

  
  VkDebugUtilsMessengerCreateInfoEXT messenger_creation_info = GetCreateMessengerInfo(); 
  if (validation_enabled_) {
    instance_creation_info.pNext = &messenger_creation_info;
    instance_creation_info.enabledLayerCount = validation_layers.size();
    instance_creation_info.ppEnabledLayerNames = validation_layers.data();
  } else {
    instance_creation_info.enabledLayerCount = 0;
    instance_creation_info.ppEnabledLayerNames = nullptr;
  }
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
  
  bool Graphics::LayerMatchesName(gsl::czstring name, const VkLayerProperties& layer) {
    return veng::streq(layer.layerName,name); 
  }

  bool Graphics::IsLayerSupported(gsl::span<VkLayerProperties> layers, gsl::czstring name) {
    return std::any_of(layers.begin(),layers.end(),std::bind_front(LayerMatchesName,name)); 
  }

  bool Graphics::AllLayersSupported(gsl::span<gsl::czstring> layers) {
    std::vector<VkLayerProperties> supported_layers = GetSupportedValidationLayers();
    return std::any_of(layers.begin(),layers.end(),std::bind_front(IsLayerSupported,supported_layers));
  }
  std::vector<VkLayerProperties> Graphics::GetSupportedValidationLayers() {
      std::uint32_t count;
      vkEnumerateInstanceLayerProperties(&count, nullptr);
      if (count ==0) {
        return {};
      }
      std::vector<VkLayerProperties> properties(count);
      vkEnumerateInstanceLayerProperties(&count, properties.data());
      return properties;
  }

  std::vector<gsl::czstring> Graphics::GetRequiredInstanceExtensions() {
      gsl::span<gsl::czstring> suggested_extensions = GetSuggestedExtensions();
      std::vector<gsl::czstring> required_extensions(suggested_extensions.size());
      std::copy(suggested_extensions.begin(),suggested_extensions.end(),required_extensions.begin());
    
    if (validation_enabled_) {
      required_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    if(!AllExtensionsSupported(required_extensions)) {
      std::exit(EXIT_FAILURE);
    }
    return required_extensions;
  }
}
