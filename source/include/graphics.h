#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <vulkan/vulkan.h>
#include <precomp.h>
#include <glfw_window.h>

namespace veng {
  class Graphics final {
    public:    
      Graphics(gsl::not_null<Window*> window);
      ~Graphics();
     
    private:

      gsl::span<gsl::czstring> GetSuggestedExtensions();   
      void CreateInstance();
      void InitilizeVulkan();
      VkInstance instance_;
      gsl::not_null<Window*> window_;
  };
}
#endif 
