#ifndef GLFW_INIT
#define GLFW_INIT
#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace veng {
  struct GlfwIntitialization {
    public:
      GlfwIntitialization();
      ~GlfwIntitialization();

      GlfwIntitialization(const GlfwIntitialization&) = delete;
      GlfwIntitialization& operator=(const GlfwIntitialization&) = delete;
    
      
  };
}

#endif
