#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "glfw_monitor.h"
struct GLFWwindow;

namespace veng {
  class Window {
    public:
      Window(gsl::czstring,glm::ivec2);
      ~Window();
      
      bool ShouldClose() const;
      glm::ivec2 GetWindowSize() const;
      bool MoveToMonitor(std::uint16_t);
      GLFWwindow* GetHandle() const;
      
    private:
      GLFWwindow* window_;
  };  
  
}//ns veng

#endif // !GLFW_WINDOW_H
