#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

// lve -> little vulkan engine
namespace lve
{
  class LveWindow
  {
    public:
      LveWindow(int w, int h, std::string name);
      ~LveWindow();

      LveWindow(const LveWindow &) = delete;
      LveWindow &operator=(const LveWindow &) = delete;

      bool shouldClose() { return glfwWindowShouldClose(window); }

      void createWindowSurface(VkInstance, VkSurfaceKHR*);
    private:
      void InitWindow();
    
      const int width;
      const int height;

      std::string windowName;
      GLFWwindow* window;
  };
}