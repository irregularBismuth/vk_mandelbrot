#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <vulkan/vulkan.h>
#include <precomp.h>

namespace veng {
  class Graphics final {
    public:    
      Graphics(gsl::not_null<Window*> window);
      ~Graphics() = default;
     
      void InitilizeVulkan();
      void CreateInstance();
    private:
      VkInstance instance_;
      gsl::not_null<Window*> window_;
  };
}
endif 
