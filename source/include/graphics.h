#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <gsl/string_span>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan.h>
#include "precomp.h"
#include <glfw_window.h>
#include <vulkan/vulkan_core.h>
#include <iostream>
namespace veng {
  static VKAPI_ATTR VkBool32 VKAPI_CALL ValidationCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
  ) {
    if (severity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
      std::cerr<<" Validation Error"<< callback_data->pMessage << std::endl;
    } else {
      std::cout<<" Validation Message"<< callback_data->pMessage << std::endl;
    }
    
  }

  static VkDebugUtilsMessengerCreateInfoEXT GetCreateMessengerInfo() {
    VkDebugUtilsMessengerCreateInfoEXT creation_info = {};
    creation_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    creation_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
    creation_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    creation_info.pfnUserCallback = ValidationCallback;
    creation_info.pUserData = nullptr;
    return creation_info;
  }
  class Graphics final {
    public:    
      Graphics(gsl::not_null<Window*> window);
      ~Graphics();
     
    private:
      
      bool LayerMatchesName(gsl::czstring name,const VkLayerProperties& layer); 
      bool IsLayerSupported(gsl::span<VkLayerProperties> layer,gsl::czstring name);  
      static bool AllLayersSupported(gsl::span<gsl::czstring> layers);
      static std::vector<VkLayerProperties> GetSupportedValidationLayers();
      static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
      std::vector<gsl::czstring> GetRequiredInstanceExtensions();
      static gsl::span<gsl::czstring> GetSuggestedExtensions();   
      static bool AllExtensionsSupported(gsl::span<gsl::czstring> extensions);
      bool ExtensionMatchesName(gsl::czstring name,const VkExtensionProperties& extension); 
      bool IsExtensionSupported(gsl::span<VkExtensionProperties> extensions,gsl::czstring name);  
      void CreateInstance();
      void InitilizeVulkan();
      VkInstance instance_;
      gsl::not_null<Window*> window_;
      bool validation_enabled_ = false;
  };
}
#endif 
