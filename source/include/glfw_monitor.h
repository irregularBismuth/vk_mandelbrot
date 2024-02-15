#ifndef GLFW_MONITOR
#define GLFW_MONITOR
#include "precomp.h"
#include "glm/glm.hpp"
struct GLFWmonitor;
struct GLFWwindow;

namespace veng {
  gsl::span<GLFWmonitor*> GetMonitors();
  glm::ivec2 GetMonitorPosition(gsl::not_null<GLFWmonitor*>);
  glm::ivec2 GetMonitorWorkareaSize(gsl::not_null<GLFWmonitor*>);
  void MoveWindowToMonitor(gsl::not_null<GLFWwindow*>,gsl::not_null<GLFWmonitor*>);  
}


#endif
