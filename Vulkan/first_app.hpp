#pragma once

#include "lve_window.hpp"
#include "lve_pipeline.hpp"

namespace lve
{
  class FirstApp
  {
    public:
      static constexpr int WIDTH = 800;
      static constexpr int HEIGHT = 600;

      void run();
    private:
      LveWindow lveWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
      LvePipeline lvePiperline{
        "shaders/simple_shaders.vert.spv",
        "shaders/simple_shaders.frag.spv"
      };
  };
}