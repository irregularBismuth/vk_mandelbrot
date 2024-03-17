#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <gsl/string_span>
#include <vulkan/vulkan.h>
#include "precomp.h"
#include <glfw_window.h>
#include <vulkan/vulkan_core.h>
namespace veng {
  class Graphics final {
    public:    
      Graphics(gsl::not_null<Window*> window);
      ~Graphics();
     
    private:
      

      static std::vector<VkExtensionProperties> GetSupportedInstanceExtensions();
      static gsl::span<gsl::czstring> GetSuggestedExtensions();   
      static bool AllExtensionsSupported(gsl::span<gsl::czstring> extensions);
      bool ExtensionMatchesName(gsl::czstring name,const VkExtensionProperties& extension); 
      bool IsExtensionSupported(gsl::span<VkExtensionProperties> extensions,gsl::czstring name);  
      void CreateInstance();
      void InitilizeVulkan();
      VkInstance instance_;
      gsl::not_null<Window*> window_;
  };
}
#endif 
