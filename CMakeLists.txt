cmake_minimum_required(VERSION 3.10)

# Set your project name
project(mandelbrot)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
# Find the Vulkan package
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
#find_package(gsl REQUIRED)
# Include Vulkan headers
include_directories(${Vulkan_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/source/include)

# Add your source files
add_executable(mandelbrot 
              source/src/main.cpp
              source/src/glfw_initialization.cpp # Add this line # Add this line
  ) 

  target_precompile_headers(mandelbrot PRIVATE "${PROJECT_SOURCE_DIR}/source/include/precomp.h")
# Link Vulkan library
target_link_libraries(mandelbrot ${Vulkan_LIBRARIES} glfw)
