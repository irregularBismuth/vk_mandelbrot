#include "glfw_monitor.h"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_int2.hpp>
#include <gsl/pointers>

namespace veng {
gsl::span<GLFWmonitor*> GetMonitors() {

  std::int32_t monitor_count = 0;
  GLFWmonitor **monitor_ptrs = glfwGetMonitors(&monitor_count);
  return gsl::span<GLFWmonitor*>(monitor_ptrs,monitor_count);

}



glm::ivec2 GetMonitorPosition(gsl::not_null<GLFWmonitor*> monitor) {
  glm::ivec2 monitor_pos;
  glfwGetMonitorPos(monitor,&monitor_pos.x,&monitor_pos.y);
  return monitor_pos;
}

glm::ivec2 GetMonitorWorkareaSize(gsl::not_null<GLFWmonitor*> monitor) {
  glm::ivec2 monitor_size;
  glfwGetMonitorWorkarea(monitor,nullptr,nullptr,&monitor_size.x,&monitor_size.y);
  return monitor_size;
}

void MoveWindowToMonitor(gsl::not_null<GLFWwindow*> window, gsl::not_null<GLFWmonitor*> monitor) {
  glm::ivec2 window_size;
  glfwGetWindowSize(window,&window_size.x,&window_size.y);
  const glm::ivec2 window_new_pos = GetMonitorPosition(monitor) + GetMonitorWorkareaSize(monitor) /2  - window_size/2; 
}


}
