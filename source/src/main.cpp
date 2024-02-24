#include "glfw_window.h"
#include <cstdlib>
#include <glm/ext/vector_float2.hpp>
#include <gsl/pointers>
#include <gsl/util>
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "glfw_initialization.h"
#include "glfw_monitor.h"
std::int32_t main(std::int32_t argc,gsl::zstring* argv) {  
  const veng::GlfwIntitialization _glfw;
  veng::Window window("VkEngine",{800,600});
  //glfwCreateWindow(800, 600, "vulkan engine",nullptr, nullptr);
  //gsl::final_action _cleanup([window]()->void {glfwDestroyWindow(window);});
  window.MoveToMonitor(1);

  while (!window.ShouldClose()) {
    glfwPollEvents();
  }

  return EXIT_SUCCESS;
}


