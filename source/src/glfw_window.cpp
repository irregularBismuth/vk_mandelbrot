#include "glfw_window.h"
#include <GLFW/glfw3.h>

namespace veng {
  Window::Window(gsl::czstring name, glm::ivec2 size) {
    window_ = glfwCreateWindow(size.x,size.y,name,nullptr,nullptr);  
    if (window_ == nullptr) {
      std::exit(EXIT_FAILURE);
    }
  }

  Window::~Window() {
    glfwDestroyWindow(window_);
  }
  glm::ivec2 Window::GetWindowSize() const {
    glm::ivec2 window_size;
    glfwGetWindowSize(window_,&window_size.x,&window_size.y);
    return window_size;
  }

  bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window_); 
  }

  GLFWwindow* Window::GetHandle() const {
    return window_;
  }
  
  bool Window::MoveToMonitor(std::uint16_t num) {
    gsl::span<GLFWmonitor*> monitors = veng::GetMonitors();
    if(num<monitors.size()) {
      veng::MoveWindowToMonitor(window_,monitors[num]);
      return true;  
    }  
    return false;
  }  
} //namespace veng
