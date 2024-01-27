cmake_minimum_required(VERSION 3.10)

# Set your project name
project(mandelbrot)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the Vulkan package
find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

# Include Vulkan headers
include_directories(${Vulkan_INCLUDE_DIRS})

# Add your source files
add_executable(mandelbrot source/src/main.cpp) # Replace 'main.cpp' with your source files

# Link Vulkan library
target_link_libraries(mandelbrot ${Vulkan_LIBRARIES} glfw)
