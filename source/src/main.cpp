#include <GLFW/glfw3.h>
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

std::int32_t main(std::int32_t argc,gsl::zstring* argv) { 
   
  
  veng::GlfwIntitialization _glfw;
  gsl::not_null<GLFWwindow*> window= glfwCreateWindow(800, 600, "vulkan engine",nullptr, nullptr);
  gsl::final_action _cleanup([window]()->void {glfwDestroyWindow(window);});
   
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  return EXIT_SUCCESS;
}


