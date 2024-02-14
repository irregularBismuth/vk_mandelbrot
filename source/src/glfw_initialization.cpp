#include "glfw_initialization.h"

namespace veng  {
  GlfwIntitialization::GlfwIntitialization() {
    if (glfwInit() != GLFW_TRUE) {
      std::exit(EXIT_FAILURE);
    } 
  }

  GlfwIntitialization::~GlfwIntitialization() {
    glfwTerminate();
  }
}
